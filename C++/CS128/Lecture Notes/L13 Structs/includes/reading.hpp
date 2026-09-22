#ifndef READING_HPP
#define READING_HPP

struct Reading {
  unsigned int sensor_id = 0;
  int celsius = 0;
  bool is_valid = false;
};

#endif
