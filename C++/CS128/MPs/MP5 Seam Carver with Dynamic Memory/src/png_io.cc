#include "png_io.hpp"

#include <zlib.h>

#include <array>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

using Bytes = std::vector<unsigned char>;
constexpr std::array<unsigned char, 8> kSignature{137, 80, 78, 71,
                                                  13,  10, 26, 10};
constexpr std::size_t kMaxFileBytes = 128 * 1024 * 1024;
constexpr unsigned int kMaxDimension = 4096;

struct PngData {
  unsigned int width = 0;
  unsigned int height = 0;
  bool interlaced = false;
  Bytes compressed;
};

struct Pass {
  unsigned int x;
  unsigned int y;
  unsigned int dx;
  unsigned int dy;
};

std::uint32_t Read32(const Bytes& bytes, std::size_t offset) {
  std::uint32_t value = 0;
  for (unsigned int index = 0; index < 4; ++index) {
    value = (value << 8) | bytes[offset + index];
  }
  return value;
}

void Append32(Bytes& bytes, std::uint32_t value) {
  for (int shift = 24; shift >= 0; shift -= 8) {
    bytes.push_back(static_cast<unsigned char>(value >> shift));
  }
}

bool LoadBytes(const std::string& path, Bytes& bytes) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);
  if (!file) {
    return false;
  }
  const auto length = file.tellg();
  if (length < 0 || static_cast<std::uint64_t>(length) > kMaxFileBytes) {
    return false;
  }
  bytes.resize(static_cast<std::size_t>(length));
  file.seekg(0);
  if (!bytes.empty()) {
    file.read(reinterpret_cast<char*>(bytes.data()), bytes.size());
  }
  return static_cast<bool>(file);
}

bool ReadHeader(const Bytes& bytes, std::size_t offset, std::size_t length,
                PngData& png) {
  if (length != 13) {
    return false;
  }
  png.width = Read32(bytes, offset);
  png.height = Read32(bytes, offset + 4);
  if (png.width == 0 || png.height == 0 || png.width > kMaxDimension ||
      png.height > kMaxDimension) {
    return false;
  }
  if (bytes[offset + 8] != 8 || bytes[offset + 9] != 2 ||
      bytes[offset + 10] != 0 || bytes[offset + 11] != 0 ||
      bytes[offset + 12] > 1) {
    return false;
  }
  png.interlaced = bytes[offset + 12] == 1;
  return true;
}

bool IsChunkName(const std::string& type) {
  for (unsigned char letter : type) {
    if (!((letter >= 'A' && letter <= 'Z') ||
          (letter >= 'a' && letter <= 'z'))) {
      return false;
    }
  }
  return type[2] >= 'A' && type[2] <= 'Z';
}

bool Parse(const Bytes& bytes, PngData& png) {
  if (bytes.size() < kSignature.size()) {
    return false;
  }
  for (std::size_t index = 0; index < kSignature.size(); ++index) {
    if (bytes[index] != kSignature[index]) {
      return false;
    }
  }
  bool header = false;
  bool data = false;
  bool data_ended = false;
  bool palette = false;
  std::size_t offset = kSignature.size();
  while (offset < bytes.size()) {
    if (bytes.size() - offset < 12) {
      return false;
    }
    const std::size_t length = Read32(bytes, offset);
    if (length > bytes.size() - offset - 12) {
      return false;
    }
    const std::string type(bytes.begin() + offset + 4,
                           bytes.begin() + offset + 8);
    if (!IsChunkName(type)) {
      return false;
    }
    const auto checksum =
        crc32(0, bytes.data() + offset + 4, static_cast<uInt>(length + 4));
    if (checksum != Read32(bytes, offset + 8 + length)) {
      return false;
    }
    if (!header && type != "IHDR") {
      return false;
    }
    if (data && type != "IDAT") {
      data_ended = true;
    }
    if (type == "IHDR") {
      if (header || !ReadHeader(bytes, offset + 8, length, png)) {
        return false;
      }
      header = true;
    } else if (type == "PLTE") {
      if (palette || data || length == 0 || length > 768 || length % 3 != 0) {
        return false;
      }
      palette = true;
    } else if (type == "IDAT") {
      if (data_ended) {
        return false;
      }
      data = true;
      png.compressed.insert(png.compressed.end(), bytes.begin() + offset + 8,
                            bytes.begin() + offset + 8 + length);
    } else if (type == "IEND") {
      return data && length == 0 && offset + 12 == bytes.size();
    } else if (type == "tRNS" || type == "acTL" || (type[0] & 32) == 0) {
      return false;
    }
    offset += length + 12;
  }
  return false;
}

std::vector<Pass> Passes(bool interlaced) {
  if (!interlaced) {
    return {{0, 0, 1, 1}};
  }
  return {{0, 0, 8, 8}, {4, 0, 8, 8}, {0, 4, 4, 8}, {2, 0, 4, 4},
          {0, 2, 2, 4}, {1, 0, 2, 2}, {0, 1, 1, 2}};
}

unsigned int PassSize(unsigned int dimension, unsigned int start,
                      unsigned int stride) {
  if (start >= dimension) {
    return 0;
  }
  return (dimension - start + stride - 1) / stride;
}

std::size_t RawSize(const PngData& png) {
  std::size_t size = 0;
  for (const Pass& pass : Passes(png.interlaced)) {
    const auto width = PassSize(png.width, pass.x, pass.dx);
    const auto height = PassSize(png.height, pass.y, pass.dy);
    if (width != 0) {
      size += (3 * static_cast<std::size_t>(width) + 1) * height;
    }
  }
  return size;
}

bool Inflate(const Bytes& compressed, std::size_t expected, Bytes& raw) {
  raw.resize(expected + 1);
  z_stream stream{};
  stream.next_in = const_cast<Bytef*>(compressed.data());
  stream.avail_in = static_cast<uInt>(compressed.size());
  stream.next_out = raw.data();
  stream.avail_out = static_cast<uInt>(raw.size());
  if (inflateInit(&stream) != Z_OK) {
    return false;
  }
  const int status = inflate(&stream, Z_FINISH);
  const bool valid = status == Z_STREAM_END && stream.total_out == expected &&
                     stream.total_in == compressed.size();
  inflateEnd(&stream);
  raw.resize(expected);
  return valid;
}

int Paeth(int left, int above, int upper_left) {
  const int prediction = left + above - upper_left;
  const int left_distance = std::abs(prediction - left);
  const int above_distance = std::abs(prediction - above);
  const int corner_distance = std::abs(prediction - upper_left);
  if (left_distance <= above_distance && left_distance <= corner_distance) {
    return left;
  }
  return above_distance <= corner_distance ? above : upper_left;
}

bool Reconstruct(Bytes& current, const Bytes& previous, unsigned char filter) {
  if (filter > 4) {
    return false;
  }
  for (std::size_t index = 0; index < current.size(); ++index) {
    const int left = index >= 3 ? current[index - 3] : 0;
    const int above = previous[index];
    const int upper_left = index >= 3 ? previous[index - 3] : 0;
    int prediction = 0;
    if (filter == 1) {
      prediction = left;
    }
    if (filter == 2) {
      prediction = above;
    }
    if (filter == 3) {
      prediction = (left + above) / 2;
    }
    if (filter == 4) {
      prediction = Paeth(left, above, upper_left);
    }
    current[index] = static_cast<unsigned char>(current[index] + prediction);
  }
  return true;
}

bool Decode(const PngData& png, const Bytes& raw,
            std::vector<std::vector<Pixel>>& pixels) {
  pixels.assign(png.height, std::vector<Pixel>(png.width));
  std::size_t offset = 0;
  for (const Pass& pass : Passes(png.interlaced)) {
    const auto width = PassSize(png.width, pass.x, pass.dx);
    const auto height = PassSize(png.height, pass.y, pass.dy);
    if (width == 0 || height == 0) {
      continue;
    }
    Bytes previous(width * 3, 0);
    for (unsigned int row = 0; row < height; ++row) {
      const unsigned char filter = raw[offset++];
      Bytes current(raw.begin() + offset, raw.begin() + offset + width * 3);
      offset += width * 3;
      if (!Reconstruct(current, previous, filter)) {
        return false;
      }
      for (unsigned int col = 0; col < width; ++col) {
        pixels[pass.y + row * pass.dy][pass.x + col * pass.dx] =
            Pixel(current[col * 3], current[col * 3 + 1], current[col * 3 + 2]);
      }
      previous.swap(current);
    }
  }
  return offset == raw.size();
}

void AppendChunk(Bytes& png, const std::string& type, const Bytes& data) {
  Append32(png, data.size());
  const std::size_t begin = png.size();
  png.insert(png.end(), type.begin(), type.end());
  png.insert(png.end(), data.begin(), data.end());
  Append32(png,
           crc32(0, png.data() + begin, static_cast<uInt>(data.size() + 4)));
}

bool Encode(const Image& image, Bytes& png) {
  if (image.GetWidth() == 0 || image.GetHeight() == 0 ||
      image.GetWidth() > kMaxDimension || image.GetHeight() > kMaxDimension) {
    return false;
  }
  Bytes raw;
  raw.reserve((image.GetWidth() * 3 + 1) * image.GetHeight());
  for (unsigned int row = 0; row < image.GetHeight(); ++row) {
    raw.push_back(0);
    for (unsigned int col = 0; col < image.GetWidth(); ++col) {
      const Pixel pixel = image.GetPixel(row, col);
      raw.push_back(static_cast<unsigned char>(pixel.GetRed()));
      raw.push_back(static_cast<unsigned char>(pixel.GetGreen()));
      raw.push_back(static_cast<unsigned char>(pixel.GetBlue()));
    }
  }
  uLongf size = compressBound(raw.size());
  Bytes compressed(size);
  if (compress2(compressed.data(), &size, raw.data(), raw.size(),
                Z_DEFAULT_COMPRESSION) != Z_OK) {
    return false;
  }
  compressed.resize(size);
  png.assign(kSignature.begin(), kSignature.end());
  Bytes header;
  Append32(header, image.GetWidth());
  Append32(header, image.GetHeight());
  header.insert(header.end(), {8, 2, 0, 0, 0});
  AppendChunk(png, "IHDR", header);
  AppendChunk(png, "IDAT", compressed);
  AppendChunk(png, "IEND", {});
  return true;
}
bool ReadPng(const std::string& path, Image* image) {
  if (image == nullptr) {
    return false;
  }
  try {
    Bytes bytes;
    PngData png;
    Bytes raw;
    std::vector<std::vector<Pixel>> pixels;
    if (!LoadBytes(path, bytes) || !Parse(bytes, png) ||
        !Inflate(png.compressed, RawSize(png), raw) ||
        !Decode(png, raw, pixels)) {
      return false;
    }
    const unsigned int kHeight = pixels.size();
    const unsigned int kWidth = pixels.empty() ? 0 : pixels[0].size();
    Image loaded(kHeight, kWidth);
    for (unsigned int row = 0; row < kHeight; ++row) {
      for (unsigned int col = 0; col < kWidth; ++col) {
        loaded.SetPixel(row, col, pixels[row][col]);
      }
    }
    *image = loaded;
    return true;
  } catch (const std::exception&) {
    return false;
  }
}

bool WritePng(const std::string& path, const Image& image) {
  try {
    Bytes png;
    if (!Encode(image, png)) {
      return false;
    }
    std::ofstream file(path, std::ios::binary);
    if (!file) {
      return false;
    }
    file.write(reinterpret_cast<const char*>(png.data()), png.size());
    file.close();
    return static_cast<bool>(file);
  } catch (const std::exception&) {
    return false;
  }
}
