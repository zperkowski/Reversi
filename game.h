#include "stdlib.h"

extern char player1_name[16];
extern char player2_name[16];
extern int mapSizeInt;
extern char mapSizeString[3];
int i, j;

int** getBoard() {
  int **board = (int**)calloc(mapSizeInt, sizeof(int*));
  for (i = 0; i < mapSizeInt; i++)
    board[i] = (int*)calloc(mapSizeInt, sizeof(int));
  return board;
}

void deleteBoard(int **board) {
  for (i = 0; i < mapSizeInt; i++)
    free(board[i]);
  free(board);
}

// Test version of drawBoard
void drawBoard(int **board) {
  for (i = 0; i < mapSizeInt; i++) {
    for (j = 0; j < mapSizeInt; j++) {
      printf("%d", board[i][j]);
    }
    printf("\n");
  }
}

// Test version of playReversi
void playReversi() {
  int **reversiBoard = getBoard();
  drawBoard(reversiBoard);
  deleteBoard(reversiBoard);
}
