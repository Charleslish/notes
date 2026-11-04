#include "doubly_linked_list.hpp"

int main() {
  DoublyLinkedList<int> dll;
  dll.InsertSorted(3);
  dll.InsertSorted(1);
  dll.InsertSorted(5);
  dll.InsertSorted(2);
  dll.InsertSorted(4);
  return 0;
}
