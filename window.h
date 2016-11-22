#ifdef __linux__

#elif _WIN32
  #include "windows.h"
  struct windowSize {
    int width;
    int height;
  };

  struct windowSize getWindowSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    struct windowSize window;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    window.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    window.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return window;
  }
#endif
