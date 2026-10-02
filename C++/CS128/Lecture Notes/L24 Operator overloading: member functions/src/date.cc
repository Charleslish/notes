#include "date.hpp"

Date::Date(int year, int month, int day)
    : year_(year), month_(month), day_(day) {
    if (year_ < kMinYear)
        year_ = kMinYear;
    else if (year_ > kMaxYear)
        year_ = kMaxYear;
    if (month_ < 1)
        month_ = 1;
    else if (month_ > kMonthsPerYear)
        month_ = kMonthsPerYear;
    if (day_ < 1)
        day_ = 1;
    else if (day_ > DaysInMonth())
        day_ = DaysInMonth();
}

int Date::GetYear() const { return year_; }
int Date::GetMonth() const { return month_; }
int Date::GetDay() const { return day_; }

Date& Date::operator++() {
  day_++;
  Normalize();
  return *this;
}

Date Date::operator++(int) {
  Date before = *this;
  ++(*this);
  return before;
}

Date& Date::operator--() {
  day_--;
  Normalize();
  return *this;
}

Date Date::operator--(int) {
  Date before = *this;
  --(*this);
  return before;
}

Date& Date::operator+=(int days) {
  day_ += LimitStep(days);
  Normalize();
  return *this;
}

Date& Date::operator-=(int days) {
  day_ -= LimitStep(days);
  Normalize();
  return *this;
}

bool Date::IsLeapYear() const{
    static constexpr int k4 = 4;
    static constexpr int k100 = 100;
    static constexpr int k400 = 400;
    return (year_ % k4 == 0 && year_ % k100 != 0) || (year_ % k400 == 0);
}
int Date::DaysInMonth() const{
    constexpr int kDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return kDays[month_ - 1] + static_cast<int>(month_ == 2 && IsLeapYear());
}
int Date::LimitStep(int days) const{
    if (days > kMaxStep) 
        return kMaxStep;
    else if (days < -kMaxStep) 
        return -kMaxStep;
    else 
        return days;
}

void Date::Normalize(){
    while (day_ > DaysInMonth()) {
        day_ -= DaysInMonth();
        month_++;
        if (month_ > kMonthsPerYear) {
            month_ -= kMonthsPerYear;
            year_++;
        }
    }
    while (day_ <= 0) {
        month_--;
        if (month_ < 1) {
            month_ += kMonthsPerYear;
            year_--;
        }
        day_ += DaysInMonth();
    }
    if(year_ > kMaxYear){
        year_ = kMaxYear;
        month_ = kMonthsPerYear;
        day_ = DaysInMonth();
    }
    else if(year_ < kMinYear){
        year_ = kMinYear;
        month_ = 1;
        day_ = 1;
    }
}
