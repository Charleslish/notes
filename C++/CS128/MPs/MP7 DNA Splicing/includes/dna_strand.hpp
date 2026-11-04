#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void PushBack(char data);
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

private:
  bool MatchAt(Node* start, const char* pattern, Node*& last) const;
  void FindLastMatch(const char* pattern, Node*& before, Node*& first,
                     Node*& last) const;
  void DeleteRange(Node* first, Node* after);

  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif
