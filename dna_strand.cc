#include "dna_strand.hpp"

#include <stdexcept>
DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {
    Node* next = head_->next;
    delete[] head_;
    head_ = next;
  }
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (&to_splice_in == this) {
    return;
  }
  if (pattern == nullptr || to_splice_in.head_ == nullptr) {
    return;
  }
  Find(pattern, to_splice_in);
}

int DNAstrand::PatternSize(const char* pattern) {
  int len = 0;
  while (*pattern != '\0') {
    len++;
    pattern++;
  }
  return len;
}

void DNAstrand::Find(const char* pattern, DNAstrand& to_splice_in) {
  Node* ending_node = head_;
  Node* starting_node = head_;
  if (IsPatternThere(pattern)) {
    Node* new_node = head_;
    int counter = 0;
    int position = 0;
    while (new_node != nullptr) {
      // std::cout << "while " << std::endl;
      if (new_node->data == pattern[0] && new_node->next != nullptr) {
        // std::cout << "this letter matches at " << counter << std::endl;
        Node* compare = new_node->next;
        if (PatternSize(pattern) == 1) {
          position = counter;
        } else {
          for (int i = 1; i < PatternSize(pattern); i++) {
            if (pattern[i] == compare->data) {
              compare = compare->next;
              if (i == PatternSize(pattern) - 1) {
                position = counter;
              }
            } else {
              break;
            }
          }
        }
      }
      new_node = new_node->next;
      counter++;
    }
    FindHelper(position, pattern, to_splice_in, starting_node, ending_node);
  } else {
    throw std::invalid_argument("no match");
  }
}
void DNAstrand::FindHelper(int position,
                           const char* pattern,
                           DNAstrand& to_splice_in,
                           Node* starting_node,
                           Node* ending_node) {
  if (position == 0) {
    for (int x = 0; x < PatternSize(pattern) - 1; x++) {
      ending_node = ending_node->next;
    }
    Replacement(to_splice_in, starting_node, ending_node, pattern, true);
  } else {
    for (int x = 0; x < position - 1; x++) {
      starting_node = starting_node->next;
    }
    ending_node = starting_node;
    for (int x = 0; x < PatternSize(pattern); x++) {
      ending_node = ending_node->next;
    }
    Replacement(to_splice_in, starting_node, ending_node, pattern, false);
  }
}
int DNAstrand::FindDNALenth() {
  int counter = 0;
  Node* new_node = head_;
  while (new_node != nullptr) {
    counter++;
    new_node = new_node->next;
  }
  return counter;
}
bool DNAstrand::IsPatternThere(const char* pattern) {
  // std::cout << "lseacrdrtdtr" << std::endl;
  bool var = true;
  Node* new_node = head_;
  int length = PatternSize(pattern);
  while (new_node != nullptr) {
    // std::cout << "looking at " << new_node->data << std::endl;
    Node* checker = new_node;
    if (new_node->data == pattern[0]) {
      // std::cout << "this letter matches helliej" << std::endl;
      for (int i = 0; i < length; i++) {
        // std::cout << i << std::endl;
        if (pattern[i] != checker->data) {
          break;
        }
        if (i == length - 1) {
          //  std::cout << "FOUND " << std::endl;
          return var;
        }
        if (checker->next != nullptr) {
          checker = checker->next;
        }
      }
    }
    new_node = new_node->next;
  }
  return false;
}

void DNAstrand::Replacement(DNAstrand& to_splice_in,
                            Node* starting_node,
                            Node* ending_node,
                            const char* pattern,
                            bool found_at_beginning) {
  if (found_at_beginning) {
    FoundAtBeginning(to_splice_in, starting_node, ending_node, pattern);
  } else {
    Node* deleter = starting_node->next;
    Node* temp = deleter->next;
    Node* end = ending_node->next;
    while (deleter != end) {
      // std::cout << "deleting " << deleter->data << std::endl;
      deleter->next = temp;
      delete deleter;
      deleter = temp;
      to_splice_in.tail_->next = temp;
      if (deleter == nullptr) {
        break;
      }
      temp = temp->next;
    }
    if (deleter == nullptr) {
      tail_ = to_splice_in.tail_;
    }
    starting_node->next = to_splice_in.head_;
  }

  to_splice_in.head_ = nullptr;
  to_splice_in.tail_ = nullptr;
  starting_node = nullptr;
  ending_node = nullptr;
}
void DNAstrand::FoundAtBeginning(DNAstrand& to_splice_in,
                                 Node* starting_node,
                                 Node* ending_node,
                                 const char* pattern) {
  if (PatternSize(pattern) == FindDNALenth()) {
    to_splice_in.tail_->next = ending_node;
    Node* temp = starting_node;
    head_ = to_splice_in.head_;

    Node* deleter = temp;
    while (deleter != nullptr) {
      // std::cout << "deleting: " << deleter->data << std::endl;
      Node* temp_del = deleter->next;
      delete deleter;
      deleter = temp_del;
    }
  } else {
    Node* deleter = starting_node;
    Node* temp = deleter->next;
    Node* end = ending_node->next;
    while (deleter != end) {
      // std::cout << "deleting " << deleter->data << std::endl;
      deleter->next = temp;
      delete deleter;
      deleter = temp;
      head_ = temp;
      if (deleter == nullptr) {
        break;
      }
      temp = temp->next;
    }
    to_splice_in.tail_->next = head_;
    head_ = to_splice_in.head_;
  }
}
void DNAstrand::PushBack(char val) {
  if (head_ == nullptr) {
    head_ = tail_ = new Node(val);
  } else {
    tail_->next = new Node(val);
    tail_ = tail_->next;
  }
}
void DNAstrand::Display() {
  Node* current_node = head_;
  while (current_node != nullptr) {
    // std::cout << current_node->data << std::endl;
    current_node = current_node->next;
  }
}
void DNAstrand::IfHead(const char* pattern) {
  Node* starting_node = nullptr;
  Node* ending_node = nullptr;
  if (pattern[0] == head_->data) {
    starting_node = nullptr;
  }
  int i = 0;
  while (i < PatternSize(pattern)) {
    ending_node = starting_node->next;
    i++;
  }
}