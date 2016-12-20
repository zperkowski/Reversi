#include "stdlib.h"
// TODO: Test on Windows
#ifdef _WIN32
const char LEFT_TOP = 218;
const char RIGHT_TOP = 191;
const char LEFT_BOTTOM = 192;
const char RIGHT_BOTTOM = 217;
const char HORIZONTAL_LINE = 196;
const char VERTICAL_LINE = 179;
const char SYMBOL = 'X';
const char EMPTY_SPACE = ' ';
// TODO: Test on Linux
#elif __linux__
const char LEFT_TOP = 218;
const char RIGHT_TOP = 191;
const char LEFT_BOTTOM = 192;
const char RIGHT_BOTTOM = 217;
const char HORIZONTAL_LINE = 196;
const char VERTICAL_LINE = 179;
const char SYMBOL = 'X';
const char EMPTY_SPACE = ' ';

#else // For macOS
const char LEFT_TOP = ' ';
const char RIGHT_TOP = ' ';
const char LEFT_BOTTOM = ' ';
const char RIGHT_BOTTOM = ' ';
const char HORIZONTAL_LINE = '-';
const char VERTICAL_LINE = '|';
const char SYMBOL = 'X';
const char EMPTY_SPACE = ' ';
#endif

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
        drawableBoard[i][j] = LEFT_TOP;
      // Right top corner
      else if ((i == 0) && (j == mapSizeInt*2))
        drawableBoard[i][j] = RIGHT_TOP;
      // Left bottom corner
      else if ((i == mapSizeInt*2) && (j == 0))
        drawableBoard[i][j] = LEFT_BOTTOM;
      // Right bottom corner
      else if ((i == mapSizeInt*2) && (j == mapSizeInt*2))
        drawableBoard[i][j] = RIGHT_BOTTOM;
      // Top or bottom line
      else if (((i == 0) || (i == mapSizeInt*2)) &&
          ((j != 0) && (j != mapSizeInt*2)))
        drawableBoard[i][j] = HORIZONTAL_LINE;
      // Left or right line
      else if (((i != 0) && (i != mapSizeInt*2)) &&
          ((j == 0) || (j == mapSizeInt*2)))
        drawableBoard[i][j] = VERTICAL_LINE;
      else if ((i % 2 != 0 ) && (j % 2 != 0))
        drawableBoard[i][j] = SYMBOL;
      else
        drawableBoard[i][j] = EMPTY_SPACE;
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
