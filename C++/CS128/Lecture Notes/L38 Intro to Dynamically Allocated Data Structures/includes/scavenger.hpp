#ifndef SCAVENGER_HPP
#define SCAVENGER_HPP

#include <string>

struct FirstClue {
  std::string secret;
  int password = 0;
};

struct SecondClue {
  int* hidden_passkey = nullptr;
  char* hidden_character = nullptr;
};

struct ThirdClue {
  ThirdClue* true_third_clue = nullptr;
  std::string* final_passphrase = nullptr;
};

struct Prize {
  std::string message;
};

SecondClue* GetSecondClue(std::string secret, int password);
ThirdClue* GetDecoyThirdClue(int hidden_passkey, char hidden_character);
Prize* GetPrize(std::string final_passphrase);

Prize SolveScavengerHunt(FirstClue* first_clue);

#endif
