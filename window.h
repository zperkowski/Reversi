int i;
/**
 * Struktura, która zawiera szerokość i wysokość okna konsoli.
 **/
struct windowSize {
    int width; /**< Szerokość */
    int height; /**< Wysokość */
};


struct windowSize windowSize;

#ifdef _WIN32
#include "windows.h"
/**
* Sprawdza aktualną szerokość i wysokość okna. Wersja na Windows.
* /return Zwraca strukturę windowSize, która przechowuje aktulaną szerokość i wysokość konsoli.
*/
struct windowSize getWindowSize() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  struct windowSize window;

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  window.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  window.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

  return window;
}

char readKey() {
    switch (getch()) {
    case 72:
        return 'U';
    case 80:
        return 'D';
    case 77:
        return 'R';
    case 75:
        return 'L';
    case '\r':
        return 'E';
    case ' ':
        return 'S';
    case 'q':
    case 'Q':
        return 'Q';
    }
    return '0';
}
#else // For Linux or macOS

#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

/**
* Sprawdza aktualną szerokość i wysokość okna. Wersja na Linux oraz macOS.
* /return Zwraca strukturę windowSize, która przechowuje aktulaną szerokość i wysokość konsoli.
*/
struct windowSize getWindowSize() {
    struct winsize w;
    struct windowSize window;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    window.width = w.ws_col;
    window.height = w.ws_row;

    return window;
}

/**
 * Imitacja getch na Linux oraz macOS stworzona w celu zachowania kompatybilności między systemami operacyjnymi.
 * @return Zwraca wciśnięty klawisz.
 */
int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

/**
 * Funkcja ułatwiająca czytanie klawiszy wciśniętych przez użytkownika.
 * Zostały napisane dwie funkcje o tej samej nazwie, ale różnej implementacji dla Windows i Linux/macOS, by zachować spójność kodu.
 * @return Zwraca znak wciśnięty przez użytkownika: Strzałki: U - Up, D - Down, L - Left, R - Right; S - Spacja, E - Enter, Q - q lub Q (Quit).
 */
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
* Funkcja czyszcząca ekran, działająca na każdym systemie operacyjnym.
*/
void scr_clr() {
    windowSize = getWindowSize();
    for (i = 0; i < (windowSize.height); i++) {
        printf("\n");
    }
}

/**
 * Wypisuje tekst na środku ekranu. Bazuje na {@link getWindowSize()} - sprawdza szerokość okna.
 * Używa printf, co pozwala na kompatybilność na każdym systemie.
 * @param text Przekazywany tekst do wypisania na konsole.
 */
void printCentered(char *text) {
    windowSize = getWindowSize(); // Updates the window size
    if (windowSize.width > strlen(text)) {
        int i;
        int space = (windowSize.width - strlen(text) - 1) / 2;
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
