/** \file Reversi.c
 * Plik główny gry.
 * Ten plik spaja wszystkie pliki nagłówkowe w projekcie Reversi.
 * @author Zdzisław Perkowski
 * @version 1.0
 */
#include "menu.h"
#include "game.h"
#include "saveGame.h"

/**
 * Tablica przechowująca nazwę pierwszego gracza.
 */
char player1_name[16] = "Player 1";
/**
 * Tablica przechowująca nazwę drugiego gracza.
 */
char player2_name[16] = "Player 2";
/**
 * Zmienna przechowująca rozmiar rozgrywanej planszy.
 */
int mapSizeInt = 4;
/**
 * Zmienna przechowująca rozmiar planszy jako znak w celu łatwiejszego wyświetlania w menu.
 */
char mapSizeString[3] = "4";
/**
 * Przechowuje nazwę pliku, który przechowuje zapisane nazwy użytkowników.
 */
char *fileName = "names.rev";

/**
 * /~Polish
 * Główna funkcja, która wywołuje {@link menu()}, żeby wywołać odpowiednie zachowanie, względem wyboru gracza.
 * @param argc Ilość argumentów - nie używane.
 * @param argv Tablica argumentów - nie używane.
 * @return Zwraca kod wykonania programu.
 */
int main(int argc, char const *argv[]) {
    testFile();

    while (1) {
        switch (menu()) {
            case 0: // Play
                playReversi();
                break;
            case 1: // Player 1
                nameChanger(1, player1_name);
                saveToFile();
                break;
            case 2: // Player 2
                nameChanger(2, player2_name);
                saveToFile();
                break;
            case 3: // Map size
                mapSizeChanger();
                break;
            case 4: // Exit
                return 0;
                break;
        }
    }
}
