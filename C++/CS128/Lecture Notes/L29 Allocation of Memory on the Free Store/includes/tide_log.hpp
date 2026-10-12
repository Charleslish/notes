#ifndef TIDE_LOG_HPP
#define TIDE_LOG_HPP

struct TideLog {
  int* heights = nullptr;
  unsigned int size = 0;
  unsigned int capacity = 0;
};

TideLog MakeLog(unsigned int capacity);
void Reserve(TideLog& log, unsigned int capacity);
bool InsertAt(TideLog& log, unsigned int index, int height);
void Release(TideLog& log);

#endif
