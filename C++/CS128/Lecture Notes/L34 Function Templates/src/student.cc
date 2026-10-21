#include "student.hpp"

Student::Student(const std::string& name, double gpa)
    : name_(name), gpa_(gpa) {}

const std::string& Student::GetName() const { return name_; }

double Student::GetGpa() const { return gpa_; }

bool Student::operator>(const Student& other) const {
  return gpa_ > other.gpa_;
}
