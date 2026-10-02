#ifndef DATE_HPP
#define DATE_HPP

class Date {
 public:
  Date() = default;
  Date(int year, int month, int day);

  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;

  Date& operator++();
  Date operator++(int);
  Date& operator--();
  Date operator--(int);
  Date& operator+=(int days);
  Date& operator-=(int days);

 private:
  static constexpr int kMinYear = 1600;
  static constexpr int kMaxYear = 2400;
  static constexpr int kMonthsPerYear = 12;
  static constexpr int kMaxStep = 292559;
  static constexpr int kDefaultYear = 2000;

  bool IsLeapYear() const;
  int DaysInMonth() const;
  int LimitStep(int days) const;
  void Normalize();

  int year_ = kDefaultYear;
  int month_ = 1;
  int day_ = 1;
};

#endif
