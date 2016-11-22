#include "stdio.h"
#include "window.h"

struct windowSize windowSize;

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
  printCentered("Reversi");
}
