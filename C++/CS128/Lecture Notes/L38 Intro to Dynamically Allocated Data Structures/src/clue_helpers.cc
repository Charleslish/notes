#include "scavenger.hpp"

#include <string>

// ============================================================
// Provided helper functions, do not modify these.
// ============================================================

SecondClue* GetSecondClue(std::string secret, int password) {
  SecondClue* clue = new SecondClue();
  int passkey = password;
  for (char c : secret) {
    passkey += static_cast<int>(c);
  }
  clue->hidden_passkey = new int(passkey);
  clue->hidden_character = new char(secret.at(0));
  return clue;
}

ThirdClue* GetDecoyThirdClue(int hidden_passkey, char hidden_character) {
  ThirdClue* real = new ThirdClue();
  real->true_third_clue = nullptr;
  std::string passphrase =
      std::string(1, hidden_character) + std::to_string(hidden_passkey);
  real->final_passphrase = new std::string(passphrase);

  ThirdClue* decoy = new ThirdClue();
  decoy->true_third_clue = real;
  decoy->final_passphrase = nullptr;
  return decoy;
}

Prize* GetPrize(std::string final_passphrase) {
  Prize* prize = new Prize();
  prize->message = "You found the prize! Passphrase was: " + final_passphrase;
  return prize;
}
