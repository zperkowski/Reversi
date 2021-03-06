#include "stdio.h"
#include "string.h"
#include "window.h"

extern char player1_name[];
extern char player2_name[];
extern int mapSizeInt;
extern char mapSizeString[];

struct windowSize windowSize;

char *menu_play_unmarked = "[ ]  Play     ";
char *menu_play_marked = "[X]  Play     ";
char *menu_player1_unmarked = "[ ] Player 1: ";
char *menu_player1_marked = "[X] Player 1: ";
char *menu_player2_unmarked = "[ ] Player 2: ";
char *menu_player2_marked = "[X] Player 2: ";
char *menu_mapSize_unmarked = "[ ] Map size: ";
char *menu_mapSize_marked = "[X] Map size: ";
char *menu_exit_unmarked = "[ ]  Exit     ";
char *menu_exit_marked = "[X]  Exit     ";

// Describes where the cursor in the menu() is set.
int option_marked = 0;
// Shows if Enter key was hit.
int option_choosen = 0;

/**
 * Czyści i rysuje menu z aktywnie poruszanym kursorem [X] względem wciskanych strzałek z klawiatury.
 * Sprawdzając zmienną {@link option_marked}, ustawia odpowiedni zestaw linii tekstu.
 */
void drawMenu() {
    scr_clr();
    // Title
    printCentered("Reversi\n");
    switch (option_marked) {
        case 0:
            printCentered(menu_play_marked);
            printCentered(menu_player1_unmarked);
            printCentered(player1_name);
            printCentered(menu_player2_unmarked);
            printCentered(player2_name);
            printCentered(menu_mapSize_unmarked);
            printCentered(mapSizeString);
            printCentered(menu_exit_unmarked);
            break;
        case 1:
            printCentered(menu_play_unmarked);
            printCentered(menu_player1_marked);
            printCentered(player1_name);
            printCentered(menu_player2_unmarked);
            printCentered(player2_name);
            printCentered(menu_mapSize_unmarked);
            printCentered(mapSizeString);
            printCentered(menu_exit_unmarked);
            break;
        case 2:
            printCentered(menu_play_unmarked);
            printCentered(menu_player1_unmarked);
            printCentered(player1_name);
            printCentered(menu_player2_marked);
            printCentered(player2_name);
            printCentered(menu_mapSize_unmarked);
            printCentered(mapSizeString);
            printCentered(menu_exit_unmarked);
            break;
        case 3:
            printCentered(menu_play_unmarked);
            printCentered(menu_player1_unmarked);
            printCentered(player1_name);
            printCentered(menu_player2_unmarked);
            printCentered(player2_name);
            printCentered(menu_mapSize_marked);
            printCentered(mapSizeString);
            printCentered(menu_exit_unmarked);
            break;
        case 4:
            printCentered(menu_play_unmarked);
            printCentered(menu_player1_unmarked);
            printCentered(player1_name);
            printCentered(menu_player2_unmarked);
            printCentered(player2_name);
            printCentered(menu_mapSize_unmarked);
            printCentered(mapSizeString);
            printCentered(menu_exit_marked);
            break;
        default:
            option_marked = 0;
            break;
    }
}

#ifdef _WIN32
/**
* Funkcja dla Windows czytająca strzałki poruszające kursor w menu, inkrementując lub dekrementując zmienną {@link option_marked}.
* @return Gdy zostanie wciśnięty enter, zwraca wybraną pozycje w menu.
*/
  int menu() {
    option_choosen = 0;
    while (option_choosen == 0) {
      drawMenu();
      switch (readKey()) {
        case 'U':
          if (option_marked > 0)
            option_marked--;
          break;
        case 'D':
          if (option_marked < 4)
            option_marked++;
          break;
        case 'S':
        case 'E':
          option_choosen = 1;
          break;
      }
    }
    return option_marked;
  }
#else // For Linux or macOS

/**
 * * Funkcja dla Linux oraz macOS czytająca strzałki poruszające kursor w menu, inkrementując lub dekrementując zmienną {@link option_marked}.
 * @return Gdy zostanie wciśnięty enter, zwraca wybraną pozycje w menu.
 */
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

/**
 * Funkcja zmieniająca nazwę gracza, która musi być między 4, a 15 znakami długości.
 * @param playerNumber Przekazany identyfikator gracza - 1 lub 2.
 * @param playerName Przekazany wskaźnik na aktualną nazwę użytkownika, która podlega zmianie.
 */
void nameChanger(int playerNumber, char *playerName) {
    scr_clr();
    if (playerNumber == 1) {
        printCentered("Set new name for the first player");
        printCentered(player1_name);
    } else if (playerNumber == 2) {
        printCentered("Set new name for the second player");
        printCentered(player2_name);
    }
    printCentered("(Maximum length: 15)");
    fgets(playerName, 16, stdin);
    /* Remove trailing newline, if there. */
    if ((strlen(playerName) > 0) && (playerName[strlen(playerName) - 1] == '\n'))
        playerName[strlen(playerName) - 1] = '\0';
}

/**
 * Funkcja zmieniająca rozmiar tablicy kwadratowej do gry. Rozmiary przyjmowane są między 4x4, a 20x20
 */
void mapSizeChanger() {
    scr_clr();
    int tempMapSize;
    do {
        tempMapSize = 0;
        printCentered("Choose map size");
        printCentered("Write an even digit between 4 and 20");
        scanf("%d", &tempMapSize);
        if (tempMapSize % 2 != 0) {
            tempMapSize = 0;
        }
    } while ((tempMapSize < 4) || (tempMapSize > 20));
    mapSizeInt = tempMapSize;
#ifdef _WIN32
    itoa(mapSizeInt, mapSizeString, 10);
#else
    sprintf(mapSizeString, "%d", mapSizeInt);
    int c;
    while ((c = getchar()) != EOF && c != '\n');
#endif
}
