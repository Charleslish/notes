#ifndef SOLUTION_HPP
#define SOLUTION_HPP

class IntArray {
public:
  // you only need to define this member function:
  void PushBack(int value);

  // okay to review these member functions, but do not modify nor worry about them.
  IntArray() = default;
  unsigned int GetSize() const { return size_; }
  unsigned int GetCapacity() const { return capacity_; }
  int operator[](unsigned int index) const { return array_[index]; }
  
  // special member functions we might not have covered yet. 
  IntArray(const IntArray& rhs) = delete;
  IntArray& operator=(const IntArray& rhs) = delete;
  ~IntArray() { delete[] array_; }

private:
  unsigned int size_ = 0;
  unsigned int capacity_ = 2;
  int* array_ = new int[capacity_];
};

#endif