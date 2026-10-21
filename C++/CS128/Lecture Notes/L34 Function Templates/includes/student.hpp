#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>

class Student {
 public:
  Student(const std::string& name, double gpa);
  const std::string& GetName() const;
  double GetGpa() const;
  bool operator>(const Student& other) const;

 private:
  std::string name_;
  double gpa_ = 0.0;
};

#endif
