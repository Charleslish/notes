#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::~DNAstrand() { DeleteRange(head_, nullptr); }

void DNAstrand::PushBack(char data) {
  Node* node = new Node(data);
  if (tail_ == nullptr)
    head_ = node;
  else
    tail_->next = node;
  tail_ = node;
}

bool DNAstrand::MatchAt(Node* start, const char* pattern, Node*& last) const {
  Node* current = start;
  for (unsigned int i = 0; pattern[i] != '\0'; ++i) {
    if (current == nullptr || current->data != pattern[i])
      return false;
    last = current;
    current = current->next;
  }
  return true;
}

void DNAstrand::FindLastMatch(const char* pattern, Node*& before,
                              Node*& first, Node*& last) const {
  Node* previous = nullptr;
  Node* current = head_;
  while (current != nullptr) {
    Node* match_end = nullptr;
    if (MatchAt(current, pattern, match_end)) {
      before = previous;
      first = current;
      last = match_end;
      previous = match_end;
      current = match_end->next;
    } else {
      previous = current;
      current = current->next;
    }
  }
}

void DNAstrand::DeleteRange(Node* first, Node* after) {
  while (first != after) {
    Node* next = first->next;
    delete first;
    first = next;
  }
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (pattern == nullptr || pattern[0] == '\0' ||
      to_splice_in.head_ == nullptr || &to_splice_in == this)
    return;

  Node* before = nullptr;
  Node* first = nullptr;
  Node* last = nullptr;
  FindLastMatch(pattern, before, first, last);
  if (first == nullptr)
    throw std::runtime_error("Pattern not found");

  Node* after = last->next;
  DeleteRange(first, after);
  if (before == nullptr)
    head_ = to_splice_in.head_;
  else
    before->next = to_splice_in.head_;
  to_splice_in.tail_->next = after;
  if (after == nullptr)
    tail_ = to_splice_in.tail_;
  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
}
