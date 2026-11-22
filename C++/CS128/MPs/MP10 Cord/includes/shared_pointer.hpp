#ifndef SHARED_POINTER_HPP
#define SHARED_POINTER_HPP

enum class kSharedPointerType { kArray, kObject };

template <typename T>
class SharedPointer {
 public:
  SharedPointer(T* address, kSharedPointerType type = kSharedPointerType::kObject)
      : holder_(address), type_(type), ref_count_(new unsigned int(1)) {}
  ~SharedPointer() { Release(); }
  SharedPointer(const SharedPointer& source)
      : holder_(source.holder_), type_(source.type_), ref_count_(source.ref_count_) {
    if (ref_count_ != nullptr)
      ++*ref_count_;
  }
  SharedPointer& operator=(const SharedPointer& source) {
    if (ref_count_ == source.ref_count_)
      return *this;
    SharedPointer retained(source);
    Release();
    holder_ = retained.holder_;
    type_ = retained.type_;
    ref_count_ = retained.ref_count_;
    retained.ref_count_ = nullptr;
    return *this;
  }

  // Provided, do not modify!
  SharedPointer() = default;
  T& operator*() { return *holder_; }
  T* operator->() { return holder_; }
  const T* operator->() const { return holder_; }
  T* Get() { return holder_; }
  const T* Get() const { return holder_; }
  unsigned int UseCount() const {
    return (ref_count_ != nullptr) ? *ref_count_ : 0;
  }

 private:
  void Release() {
    if (ref_count_ == nullptr || --*ref_count_ != 0)
      return;
    if (type_ == kSharedPointerType::kArray)
      delete[] holder_;
    else
      delete holder_;
    delete ref_count_;
  }
  T* holder_ = nullptr;
  kSharedPointerType type_ = kSharedPointerType::kObject;
  unsigned int* ref_count_ = nullptr;
};

// non-member helper function declarations

// non-member helper function definitions

// member function definitions

#endif