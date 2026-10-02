#include <iostream>

#include "date.hpp"

int main() {
  const int kYear = 2024;
  const int kMonth = 2;
  const int kDay = 28;
  const int kWeeks = 3;
  const int kDaysPerWeek = 7;

  Date date(kYear, kMonth, kDay);
  std::cout << "start: " << date.GetYear() << "-" << date.GetMonth() << "-"
            << date.GetDay() << std::endl;

  const Date kBefore = date++;
  std::cout << "date++ returned: " << kBefore.GetYear() << "-"
            << kBefore.GetMonth() << "-" << kBefore.GetDay() << std::endl;
  std::cout << "after date++: " << date.GetYear() << "-" << date.GetMonth()
            << "-" << date.GetDay() << std::endl;

  ++date;
  std::cout << "after ++date: " << date.GetYear() << "-" << date.GetMonth()
            << "-" << date.GetDay() << std::endl;

  date += kWeeks * kDaysPerWeek;
  std::cout << "after += 21: " << date.GetYear() << "-" << date.GetMonth()
            << "-" << date.GetDay() << std::endl;

  date -= kDaysPerWeek;
  --date;
  std::cout << "after -= 7 and --date: " << date.GetYear() << "-"
            << date.GetMonth() << "-" << date.GetDay() << std::endl;
  return 0;
}
