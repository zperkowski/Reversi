int i;
struct windowSize {
  int width;
  int height;
};

#ifdef __linux__
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

#elif _WIN32
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
#endif

/**
* It clears screen.
* Tested on Linux. Should work on Windows.
*/
void scr_clr() {
  struct windowSize windowSize = getWindowSize();
  for (i = 0; i < (windowSize.width*windowSize.height); i++) {
    printf(" ");
  }
}
