#include "stdio.h"
#include "string.h"
#include "unistd.h"

extern char player1_name[];
extern char player2_name[];
extern char *fileName;

/**
 * Zapisuje do pliku, którego ścieżka jest zapisana w Reversi.c.
 */
void saveToFile() {
    FILE *file;
    file = fopen(fileName, "w");
    fprintf(file, "%s\n%s\n", player1_name, player2_name);
    fclose(file);
}

/**
 * Odczytuje z pliku, którego ścieżka jest zapisana w Reversi.c.
 */
void readFromFile() {
    FILE *file;
    file = fopen(fileName, "r");
    fgets(player1_name, 16, file);
    fgets(player2_name, 16, file);
    /* Remove trailing newline, if there. */
    if ((strlen(player1_name) > 0) && (player1_name[strlen(player1_name) - 1] == '\n'))
        player1_name[strlen(player1_name) - 1] = '\0';
    if ((strlen(player2_name) > 0) && (player2_name[strlen(player2_name) - 1] == '\n'))
        player2_name[strlen(player2_name) - 1] = '\0';
    fclose(file);
}

/**
 * Sprawdza czy istnieje plik. Jeżeli istnieje, czyta z niego zapisane nazwy graczy.
 * Jeżeli nie istnieje, zapisuje do pliku standardowe nazwy graczy.
 */
void testFile() {
    if (access(fileName, F_OK) != -1) {
        // file exists
        readFromFile();
    } else {
        // file doesn't exist
        saveToFile();
    }
}
