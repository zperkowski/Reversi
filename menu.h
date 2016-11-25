#include "stdio.h"
#include "string.h"
#include "window.h"

#ifdef __linux__
#include <termios.h>
#include <unistd.h>

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
#endif

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

// Describes where the cursor in the menu() is set.
int option_marked = 0;
// Shows if Enter key was hit.
int option_choosen = 0;

/**
* Prints text in the middle of console. Window size is returned from
* getWindowSize() in window.h. Based on printf so it works
* on Linux and Windows.
*/
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
    scr_clr();
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
#elif __linux__
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
