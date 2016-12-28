int i;
struct windowSize {
  int width;
  int height;
};


struct windowSize windowSize;

#ifdef _WIN32
/**
* getWindowsSize() checks the width and height of the console and
* returns the struct windowSize. Windows version.
*/
#include "windows.h"
  struct windowSize getWindowSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    struct windowSize window;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    window.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    window.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return window;
  }

#else // For Linux or macOS
  #include <termios.h>
  #include <sys/ioctl.h>
  #include <unistd.h>
  #include <string.h> // Work without including on Windows

  /**
  * getWindowsSize() checks the width and height of the console and
  * returns the struct windowSize. Linux version.
  */
  struct windowSize getWindowSize() {
    struct winsize w;
    struct windowSize window;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    window.width = w.ws_col;
    window.height = w.ws_row;

    return window;
  }

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
// TODO: Test readKey on Linux
// TODO: Write readKey for Windows
  char readKey() {
    char input;
      input = getch();
      if (input == '\033') {
        getch();
        switch (getch()) {
          case 'A':
            return 'U';
          case 'B':
            return 'D';
          case 'C':
            return 'R';
          case 'D':
            return 'L';
        }
      } else {
        if (input == '\n')
          return 'E';
        else if (input == ' ')
          return 'S';
        else if (input == 'q' || input == 'Q')
          return 'Q';
      }
    return '0';
  }
#endif

/**
* It clears screen.
* Tested on Linux and Windows.
*/
void scr_clr() {
  windowSize = getWindowSize();
  for (i = 0; i < (windowSize.width*windowSize.height); i++) {
    printf(" ");
  }
}

/**
* Prints text in the middle of console. Window size is returned from
* getWindowSize() in window.h. Based on printf so it works
* on Linux and Windows.
*/
void printCentered(char *text) {
  windowSize = getWindowSize(); // Updates the window size
  if (windowSize.width > strlen(text)) {
    int i;
    int space = (windowSize.width - strlen(text)-1) / 2;
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
