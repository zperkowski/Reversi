#include "stdio.h"
#include "string.h"
#include "window.h"

extern char player1_name[];
extern char player2_name[];
extern int mapSizeInt;
extern char mapSizeString[];

struct windowSize windowSize;

char *menu_play_unmarked = "[ ]  Play     ";
char *menu_play_marked = "[X]  Play     ";
char *menu_player1_unmarked = "[ ] Player 1: ";
char *menu_player1_marked = "[X] Player 1: ";
char *menu_player2_unmarked = "[ ] Player 2: ";
char *menu_player2_marked = "[X] Player 2: ";
char *menu_mapSize_unmarked = "[ ] Map size: ";
char *menu_mapSize_marked = "[X] Map size: ";
char *menu_exit_unmarked = "[ ]  Exit     ";
char *menu_exit_marked = "[X]  Exit     ";

// Describes where the cursor in the menu() is set.
int option_marked = 0;
// Shows if Enter key was hit.
int option_choosen = 0;

void drawMenu() {
    scr_clr();
    // Title
    printCentered("Reversi\n");
    switch (option_marked) {
      case 0:
        printCentered(menu_play_marked);
        printCentered(menu_player1_unmarked);
        printCentered(player1_name);
        printCentered(menu_player2_unmarked);
        printCentered(player2_name);
        printCentered(menu_mapSize_unmarked);
        printCentered(mapSizeString);
        printCentered(menu_exit_unmarked);
        break;
      case 1:
        printCentered(menu_play_unmarked);
        printCentered(menu_player1_marked);
        printCentered(player1_name);
        printCentered(menu_player2_unmarked);
        printCentered(player2_name);
        printCentered(menu_mapSize_unmarked);
        printCentered(mapSizeString);
        printCentered(menu_exit_unmarked);
        break;
      case 2:
        printCentered(menu_play_unmarked);
        printCentered(menu_player1_unmarked);
        printCentered(player1_name);
        printCentered(menu_player2_marked);
        printCentered(player2_name);
        printCentered(menu_mapSize_unmarked);
        printCentered(mapSizeString);
        printCentered(menu_exit_unmarked);
        break;
      case 3:
        printCentered(menu_play_unmarked);
        printCentered(menu_player1_unmarked);
        printCentered(player1_name);
        printCentered(menu_player2_unmarked);
        printCentered(player2_name);
        printCentered(menu_mapSize_marked);
        printCentered(mapSizeString);
        printCentered(menu_exit_unmarked);
        break;
      case 4:
        printCentered(menu_play_unmarked);
        printCentered(menu_player1_unmarked);
        printCentered(player1_name);
        printCentered(menu_player2_unmarked);
        printCentered(player2_name);
        printCentered(menu_mapSize_unmarked);
        printCentered(mapSizeString);
        printCentered(menu_exit_marked);
        break;
      default:
        option_marked = 0;
        break;
    }
}

#ifdef _WIN32
  int menu() {
    option_choosen = 0;
    while (option_choosen == 0) {
      drawMenu();
      switch (getch()) {
        case 72:
          if (option_marked > 0)
            option_marked--;
          break;
        case 80:
          if (option_marked < 4)
            option_marked++;
          break;
        case '\r':
          option_choosen = 1;
          break;
      }
    }
    return option_marked;
  }
#else // For Linux or macOS
  int menu() {
    option_choosen = 0;
    char in;
    while (option_choosen == 0) {
      drawMenu();
      in = getch();
      if (in == '\033') {
        getch();
        switch (getch()) {
          case 'A':
            if (option_marked > 0)
              option_marked--;
            break;
          case 'B':
            if (option_marked < 4)
              option_marked++;
            break;
        }
      } else {
        if (in == '\n')
          option_choosen = 1;
      }
    }
    return option_marked;
  }
#endif

void nameChanger(int playerNumber, char *playerName) {
  scr_clr();
  if (playerNumber == 1) {
    printCentered("Set new name for the first player");
    printCentered(player1_name);
  }
  else if (playerNumber == 2) {
    printCentered("Set new name for the second player");
    printCentered(player2_name);
  }
  printCentered("(Maximum length: 15)");
  scanf("%15s", playerName);
  // Clear a excess of the input
  int c;
  while ((c = getchar()) != EOF && c != '\n');
}
// TODO: mapSizeChanger doesn't work on macOS
void mapSizeChanger() {
  scr_clr();
  int tempMapSize;
  do {
    tempMapSize = 0;
    printCentered("Choose map size");
    printCentered("Write an even digit between 4 and 20");
    scanf("%d", &tempMapSize);
    if (tempMapSize %2 != 0) {
        tempMapSize = 0;
    }
  } while ((tempMapSize < 4) || (tempMapSize > 20));
  mapSizeInt = tempMapSize;
  #ifdef _WIN32
  itoa(mapSizeInt, mapSizeString, 10);
  #else
  sprintf(mapSizeString, "%d", mapSizeInt);
  int c;
  while ((c = getchar()) != EOF && c != '\n');
  #endif
}
