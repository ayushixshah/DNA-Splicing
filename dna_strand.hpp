#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include <cassert>

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  int PatternSize(const char* pattern);
  void Backwards(const char* pattern, DNAstrand& to_splice_in);
  void Delete(char input);
  int FindDNALenth();
  void Find(const char* pattern, DNAstrand& to_splice_in);
  void FindHelper(int position,
                  const char* pattern,
                  DNAstrand& to_splice_in,
                  Node* starting_node,
                  Node* ending_node);
  bool IsPatternThere(const char* pattern);
  void Replacement(DNAstrand& to_splice_in,
                   Node* starting_node,
                   Node* ending_node,
                   const char* pattern,
                   bool found_at_beginning);
  void FoundAtBeginning(DNAstrand& to_splice_in,
                        Node* starting_node,
                        Node* ending_node,
                        const char* pattern);
  void PushBack(char value);
  void Display();
  void IfHead(const char* pattern);
  void IfMiddle(const char* pattern);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif