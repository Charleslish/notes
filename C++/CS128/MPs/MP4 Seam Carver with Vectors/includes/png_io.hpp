#ifndef PNG_IO_HPP
#define PNG_IO_HPP

#include <string>

#include "image.hpp"

bool ReadPng(const std::string& path, Image* image);
bool WritePng(const std::string& path, const Image& image);

#endif
