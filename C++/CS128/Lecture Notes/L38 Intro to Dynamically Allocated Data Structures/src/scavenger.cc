#include "scavenger.hpp"

#include <string>

Prize SolveScavengerHunt(FirstClue* first_clue) {
  SecondClue* second =
      GetSecondClue(first_clue->secret, first_clue->password);
  ThirdClue* decoy = GetDecoyThirdClue(*second->hidden_passkey,
                                       *second->hidden_character);
  ThirdClue* real = decoy->true_third_clue;
  Prize* prize = GetPrize(*real->final_passphrase);
  Prize result = *prize;

  delete prize;
  delete real->final_passphrase;
  delete real;
  delete decoy;
  delete second->hidden_passkey;
  delete second->hidden_character;
  delete second;

  return result;
}
