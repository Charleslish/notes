#include "solution.hpp"

#include <iostream>

int Obfuscate(int input, int iter) {
    int shift = (iter % 4) + 1;
    for (int i = 0; i < shift; ++i) 
        input = (input + 3) % 10;
    return input;
}

char Obfuscate(char input, int iter) {
    int digit = static_cast<int>(input);
    const int kThree = 3;
    int result;
    if (iter % kThree == 0)
        result = 9 - digit;
    else if (iter % kThree == 1)
        result = (digit + 2) % 10;
    else
        result = (digit * 3) % 10;
    return 'A' + result;
}

void EncryptCreditCard(unsigned long long card_number) {
  int pos = 0;
  int checksum = 0;
  const int kDecimal = 10;
  const int kEven = 2;
  while (card_number > 0) {
    if ((card_number % kDecimal) % kEven == 1) {  // odd
        char temp = Obfuscate(static_cast<char>(card_number % kDecimal), pos);
        checksum += temp;
        std::cout << temp;
    } 
    else {  // even
        int temp = Obfuscate(static_cast<int>(card_number % kDecimal), pos);
        checksum += temp;
        std::cout << temp;
    }
    ++pos;
    card_number /= kDecimal;
  }
  std::cout << checksum;
  return;
}
