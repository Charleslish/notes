#include <iostream>
#include <vector>

#include "frame_stack.hpp"

int main() {
  constexpr int kFirstSessionMinutes = 38;
  constexpr int kNoSessions = 0;
  constexpr int kNoLastSession = -1;
  constexpr unsigned int kLogSessionLocals = 1;
  constexpr unsigned int kReportLastSessionLocals = 2;
  constexpr unsigned int kLoggedPosition = 1;
  constexpr unsigned int kLastPosition = 1;

  FrameStack stack;

  const std::vector<int> kLogSessionArguments = {kFirstSessionMinutes};
  const bool kPushedLog =
      stack.Push(kLogSessionArguments, kLogSessionLocals);
  std::cout << "push LogSession(" << kFirstSessionMinutes
            << "): " << kPushedLog << ", stack pointer "
            << stack.StackPointer() << std::endl;

  const bool kWroteLogged = stack.Write(kLoggedPosition, kFirstSessionMinutes);
  std::cout << "write kLogged: " << kWroteLogged << std::endl;

  const bool kPopped = stack.Pop();
  std::cout << "pop: " << kPopped << ", stack pointer " << stack.StackPointer()
            << ", depth " << stack.Depth() << std::endl;

  const std::vector<int> kReportArguments = {kNoSessions};
  const bool kPushedReport =
      stack.Push(kReportArguments, kReportLastSessionLocals);
  std::cout << "push ReportLastSession(" << kNoSessions
            << "): " << kPushedReport << ", stack pointer "
            << stack.StackPointer() << std::endl;

  int last = kNoLastSession;
  const bool kReadLast = stack.Read(kLastPosition, &last);
  std::cout << "read last: " << kReadLast << ", value " << last << std::endl;

  const Frame* const kTop = stack.Top();
  if (kTop != nullptr) {
    std::cout << "top frame: start " << kTop->start << ", "
              << kTop->parameter_count << " parameter(s), "
              << kTop->local_count << " local(s)" << std::endl;
  }
  return 0;
}
