#include "menu.h"

char player1_name[16] = "Player 1";
char player2_name[16] = "Player 2";

int main(int argc, char const *argv[]) {
  while (1) {
    switch (menu()) {
      case 0: // Play

        break;
      case 1: // Player 1
        nameChanger(1, player1_name);
        break;
      case 2: // Player 2
        nameChanger(2, player2_name);
        break;
      case 3: // Map size

        break;
      case 4: // Exit
        return 0;
        break;
    }
  }
}
