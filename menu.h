#include "stdio.h"
#include "string.h"
#include "window.h"

struct windowSize windowSize;

char *menu_play_unmarked = "[ ] Play";
char *menu_play_marked = "[X] Play";
char *menu_player1_unmarked = "[ ] Player 1: ";
char *menu_player1_marked = "[X] Player 1: ";
char *menu_player2_unmarked = "[ ] Player 2: ";
char *menu_player2_marked = "[X] Player 2: ";
char *menu_mapSize_unmarked = "[ ] Map size: ";
char *menu_mapSize_marked = "[X] Map size: ";
char *menu_exit_unmarked = "[ ] Exit";
char *menu_exit_marked = "[X] Exit";

int option_marked = 0;
int option_choosen = 0;

void printCentered(char *text) {
  windowSize = getWindowSize(); // Updates the window size
  if (windowSize.width > strlen(text)) {
    int i;
    int space = (windowSize.width - strlen(text)) / 2;
    for (i = 0; i < space; i++)
      printf(" ");
    printf("%s", text);
    for (i = 0; i < space; i++)
      printf(" ");
  } else {
    printf("%s", text);
  }
  printf("\n");
}

void drawMenu() {
    // Title
    printCentered("Reversi\n");
    switch (option_marked) {
      case 0:
        printCentered(menu_play_marked);
        printCentered(menu_player1_unmarked);
        printCentered(menu_player2_unmarked);
        printCentered(menu_mapSize_unmarked);
        printCentered(menu_exit_unmarked);
        break;
      case 1:
        printCentered(menu_play_unmarked);
        printCentered(menu_player1_marked);
        printCentered(menu_player2_unmarked);
        printCentered(menu_mapSize_unmarked);
        printCentered(menu_exit_unmarked);
        break;
      case 2:
        printCentered(menu_play_unmarked);
        printCentered(menu_player1_unmarked);
        printCentered(menu_player2_marked);
        printCentered(menu_mapSize_unmarked);
        printCentered(menu_exit_unmarked);
        break;
      case 3:
        printCentered(menu_play_unmarked);
        printCentered(menu_player1_unmarked);
        printCentered(menu_player2_unmarked);
        printCentered(menu_mapSize_marked);
        printCentered(menu_exit_unmarked);
        break;
      case 4:
        printCentered(menu_play_unmarked);
        printCentered(menu_player1_unmarked);
        printCentered(menu_player2_unmarked);
        printCentered(menu_mapSize_unmarked);
        printCentered(menu_exit_marked);
        break;
      default:
        option_marked = 0;
        break;
    }
}

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
