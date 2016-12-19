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
// TODO: Special ASCII characters doens't work on macOS
char** getDrawableBoard(int** board) {
  scr_clr();
  char **drawableBoard = (char**)calloc(mapSizeInt*2+1, sizeof(char*));
  for (i = 0; i < mapSizeInt*2+1; i++)
    drawableBoard[i] = (char*)calloc(mapSizeInt*2+1, sizeof(char));
  for (i = 0; i < mapSizeInt*2+1; i++) {
    for (j = 0; j < mapSizeInt*2+1; j++) {
      // Left top corner
      if ((i == 0) && (j == 0))
        drawableBoard[i][j] = 218;
      // Right top corner
      else if ((i == 0) && (j == mapSizeInt*2))
        drawableBoard[i][j] = 191;
      // Left bottom corner
      else if ((i == mapSizeInt*2) && (j == 0))
        drawableBoard[i][j] = 192;
      // Right bottom corner
      else if ((i == mapSizeInt*2) && (j == mapSizeInt*2))
        drawableBoard[i][j] = 217;
      // Top or bottom line
      else if (((i == 0) || (i == mapSizeInt*2)) &&
          ((j != 0) && (j != mapSizeInt*2)))
        drawableBoard[i][j] = 196;
      // Left or right line
      else if (((i != 0) && (i != mapSizeInt*2)) &&
          ((j == 0) || (j == mapSizeInt*2)))
        drawableBoard[i][j] = 179;
      else if ((i % 2 != 0 ) && (j % 2 != 0))
        drawableBoard[i][j] = 'X';
      else
        drawableBoard[i][j] = ' ';
    }
  }
  return drawableBoard;
}

void deleteBoard(int **board) {
  for (i = 0; i < mapSizeInt; i++)
    free(board[i]);
  free(board);
}

void deleteDrawableBoard(char **board) {
  for (i = 0; i < mapSizeInt*2+1; i++)
    free(board[i]);
  free(board);
}

void drawBoard(char **board) {
  for (i = 0; i < mapSizeInt*2+1; i++) {
      printCentered(board[i]);
  }
}

// Test version of playReversi
void playReversi() {
  int **reversiBoard = getBoard();
  char **reversiDrawableBoard = getDrawableBoard(reversiBoard);
  drawBoard(reversiDrawableBoard);
  deleteBoard(reversiBoard);
  deleteDrawableBoard(reversiDrawableBoard);
}
