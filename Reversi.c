#include "menu.h"
#include "game.h"
/**
* @author Zdzisław Perkowski
* @version 1.0
*/
char player1_name[16] = "Player 1";
char player2_name[16] = "Player 2";
int mapSizeInt = 4;
char mapSizeString[3] = "4";

int main(int argc, char const *argv[]) {
  while (1) {
    switch (menu()) {
      case 0: // Play
        playReversi();
        break;
      case 1: // Player 1
        nameChanger(1, player1_name);
        break;
      case 2: // Player 2
        nameChanger(2, player2_name);
        break;
      case 3: // Map size
        mapSizeChanger();
        break;
      case 4: // Exit
        return 0;
        break;
    }
  }
}
