#include "stdlib.h"

#ifdef _WIN32
const char LEFT_TOP = 218;
const char RIGHT_TOP = 191;
const char LEFT_BOTTOM = 192;
const char RIGHT_BOTTOM = 217;
const char HORIZONTAL_LINE = 196;
const char VERTICAL_LINE = 179;
const char SYMBOL_1 = 'X';
const char SYMBOL_2 = 'O';
const char CURSOR = '_';
const char EMPTY_SPACE = ' ';
// TODO: Test on Linux
#elif __linux__
const char LEFT_TOP = 218;
const char RIGHT_TOP = 191;
const char LEFT_BOTTOM = 192;
const char RIGHT_BOTTOM = 217;
const char HORIZONTAL_LINE = 196;
const char VERTICAL_LINE = 179;
const char SYMBOL_1 = 'X';
const char SYMBOL_2 = 'O';
const char CURSOR = '_';
const char EMPTY_SPACE = ' ';

#else // For macOS
const char LEFT_TOP = ' ';
const char RIGHT_TOP = ' ';
const char LEFT_BOTTOM = ' ';
const char RIGHT_BOTTOM = ' ';
const char HORIZONTAL_LINE = '-';
const char VERTICAL_LINE = '|';
const char SYMBOL_1 = 'X';
const char SYMBOL_2 = 'O';
const char CURSOR = '_';
const char EMPTY_SPACE = ' ';
#endif

extern char player1_name[16];
extern char player2_name[16];
extern int mapSizeInt;
extern char mapSizeString[3];

int **reversiBoard;
char **reversiDrawableBoard;

int currentPlayer;
int cursorX = 0;
int cursorY = 0;

int i, j, x, y;

/**
 * Ustawia kursor na planszy do gry w wolnym miejscu, gdy zostanie wykonane bicie.
 * @return Zwraca 0, jeżeli się znaleźć wolne pole i ustawić kursor. W przeciwnym wypadku zwraca 1.
 */
int setCursor() {
    for (x = 0; x < mapSizeInt; x++) {
        for (y = 0; y < mapSizeInt; y++) {
            if (abs(cursorX - x) >= 0 && cursorX + x < mapSizeInt && abs(cursorY - y) >= 0 &&
                cursorY + y < mapSizeInt) {
                if (reversiBoard[abs(cursorY - y)][abs(cursorX - x)] == 0) {
                    cursorY = abs(cursorY - y);
                    cursorX = abs(cursorX - x);
                    return 0;
                } else if (reversiBoard[cursorY + y][cursorX + x] == 0) {
                    cursorY = cursorY + y;
                    cursorX = cursorX + x;
                    return 0;
                }
            }
        }
    }
    return 1;
}

/**
 * Inicjalizuje tablice int zgodnie z rozmiarem podanym przez użytkownika {@link mapSizeInt}.
 * @return Zwraca wygenerowaną tablicę int'ową, która zawiera same zera.
 */
int **initBoard() {
    int **board = (int **) calloc(mapSizeInt, sizeof(int *));
    for (i = 0; i < mapSizeInt; i++)
        board[i] = (int *) calloc(mapSizeInt, sizeof(int));

    // Initial first player's symbols
    board[(mapSizeInt / 2) - 1][mapSizeInt / 2] = 1;
    board[mapSizeInt / 2][(mapSizeInt / 2) - 1] = 1;

    //Initial second player's symbols
    board[mapSizeInt / 2][mapSizeInt / 2] = 2;
    board[(mapSizeInt / 2) - 1][(mapSizeInt / 2) - 1] = 2;

    currentPlayer = 1;

    return board;
}

/**
 * Inicjalizuje tablicę opartą na znakach w celu wyświetlania jej na ekranie konsoli.
 * Dodaje przestrzeń między grywalnymi polami oraz tworzy obramowanie planszy.
 * @param board to przjmowana tablica int z aktyalnym stanem rozgrywki.
 * @return Zwraca wygenerowaną tablicę, która zawiera odwzorowaną tablicę podaną jako argument oraz z uwzględnionym kursorem.
 */
char **initDrawableBoard(int **board) {
    scr_clr();
    char **drawableBoard = (char **) calloc(mapSizeInt * 2 + 1, sizeof(char *));
    for (i = 0; i < mapSizeInt * 2 + 1; i++)
        drawableBoard[i] = (char *) calloc(mapSizeInt * 2 + 1, sizeof(char));
    for (i = 0; i < mapSizeInt * 2 + 1; i++) {
        for (j = 0; j < mapSizeInt * 2 + 1; j++) {
            // Left top corner
            if ((i == 0) && (j == 0))
                drawableBoard[i][j] = LEFT_TOP;
                // Right top corner
            else if ((i == 0) && (j == mapSizeInt * 2))
                drawableBoard[i][j] = RIGHT_TOP;
                // Left bottom corner
            else if ((i == mapSizeInt * 2) && (j == 0))
                drawableBoard[i][j] = LEFT_BOTTOM;
                // Right bottom corner
            else if ((i == mapSizeInt * 2) && (j == mapSizeInt * 2))
                drawableBoard[i][j] = RIGHT_BOTTOM;
                // Top or bottom line
            else if (((i == 0) || (i == mapSizeInt * 2)) &&
                     ((j != 0) && (j != mapSizeInt * 2)))
                drawableBoard[i][j] = HORIZONTAL_LINE;
                // Left or right line
            else if (((i != 0) && (i != mapSizeInt * 2)) &&
                     ((j == 0) || (j == mapSizeInt * 2)))
                drawableBoard[i][j] = VERTICAL_LINE;
            else if ((i % 2 != 0) && (j % 2 != 0))
                drawableBoard[i][j] = EMPTY_SPACE;    // Space between playable fields
            else
                drawableBoard[i][j] = EMPTY_SPACE;    // Playable fields
        }
    }

    for (i = 0; i < mapSizeInt; i++) {
        for (j = 0; j < mapSizeInt; j++) {
            if (board[i][j] == 1) {
                drawableBoard[(i * 2) + 1][(j * 2) + 1] = SYMBOL_1;
            } else if (board[i][j] == 2) {
                drawableBoard[(i * 2) + 1][(j * 2) + 1] = SYMBOL_2;
            }
        }
    }

    drawableBoard[(cursorY * 2) + 1][(cursorX * 2) + 1] = CURSOR;

    return drawableBoard;
}

/**
 * Zwalnia pamięć używaną przez tablicę liczbową.
 * @param board Tablica, którą należy usunąć.
 */
void deleteBoard(int **board) {
    for (i = 0; i < mapSizeInt; i++)
        free(board[i]);
    free(board);
}

/**
 * Zwalnia pamięć używaną przez tablicę znakową.
 * @param board Tablica, którą należy usunąć.
 */
void deleteDrawableBoard(char **board) {
    for (i = 0; i < mapSizeInt * 2 + 1; i++)
        free(board[i]);
    free(board);
}

/**
 * Rysuje tablicę znakową za pomocą {@link printCentered()}.
 * @param board Tablica przekazana do rysowania.
 */
void drawBoard(char **board) {
    for (i = 0; i < mapSizeInt * 2 + 1; i++) {
        printCentered(board[i]);
    }
}

/**
 * Przesuwa kursor w górę, jeżeli po linii prostej jest możliwe postawienie kursora.
 * Jeżeli nie znajdzie, szuka miejsca na obszarze w kształcie trójkąta.
 * @param board Przyjmuje tablicę z aktualnym stanem rozgrywki.
 */
void moveUp(int **board) {
    // Moves up or stops when in the next step cursorY will be outside the board
    for (y = 0; (cursorY - y) > 0; y++) {
        // First checks if there's free space directly above previous step
        if (board[cursorY - (y + 1)][cursorX] == 0) {
            cursorY -= (y + 1);
            break;
        } else {
            // If there isn't, looks for a free field in triangle shape
            // 1, 3, 5, 7 fields in the width
            for (x = cursorX - y - 1; y < (cursorX - y - 1) + (1 + (y * 2)); x++) {
                // When is out of range continues looking for other fields
                if (x < 0 || x >= mapSizeInt) {
                    continue;
                }
                // When finds a free field, changes the cursor coordinates
                if (board[y][x] == 0) {
                    cursorX = x;
                    cursorY = y;
                    break;
                }
            }
        }
    }
}

/**
 * Przesuwa kursor w dół, jeżeli po linii prostej jest możliwe postawienie kursora.
 * Jeżeli nie znajdzie, szuka miejsca na obszarze w kształcie trójkąta.
 * @param board Przyjmuje tablicę z aktualnym stanem rozgrywki.
 */
void moveDown(int **board) {
    for (y = 0; (cursorY + y) < mapSizeInt - 1; y++) {
        if (board[cursorY + (y + 1)][cursorX] == 0) {
            cursorY += (y + 1);
            break;
        } else {
            for (x = cursorX - y - 1; y < (cursorX - y - 1) + (1 + (y * 2)); x++) {
                if (x < 0 || x >= mapSizeInt) {
                    continue;
                }
                if (board[y][x] == 0) {
                    cursorX = x;
                    cursorY = y;
                    break;
                }
            }
        }
    }
}

/**
 * Przesuwa kursor w lewo, jeżeli po linii prostej jest możliwe postawienie kursora.
 * Jeżeli nie znajdzie, szuka miejsca na obszarze w kształcie trójkąta.
 * @param board Przyjmuje tablicę z aktualnym stanem rozgrywki.
 */
void moveLeft(int **board) {
    for (x = 0; (cursorX - x) > 0; x++) {
        if (board[cursorX - (x + 1)][cursorY] == 0) {
            cursorX -= (x + 1);
            break;
        } else {
            for (y = cursorY - x - 1; x < (cursorY - x - 1) + (1 + (x * 2)); y++) {
                if (y < 0 || y >= mapSizeInt) {
                    continue;
                }
                if (board[y][x] == 0) {
                    cursorX = x;
                    cursorY = y;
                    break;
                }
            }
        }
    }
}

/**
 * Przesuwa kursor w prawo, jeżeli po linii prostej jest możliwe postawienie kursora.
 * Jeżeli nie znajdzie, szuka miejsca na obszarze w kształcie trójkąta.
 * @param board Przyjmuje tablicę z aktualnym stanem rozgrywki.
 */
void moveRight(int **board) {
    for (x = 0; (cursorX + x) < mapSizeInt - 1; x++) {
        if (board[cursorX + (x + 1)][cursorY] == 0) {
            cursorX += (x + 1);
            break;
        } else {
            for (y = cursorY - x - 1; x < (cursorY - x - 1) + (1 + (x * 2)); y++) {
                if (y < 0 || y >= mapSizeInt) {
                    continue;
                }
                if (board[y][x] == 0) {
                    cursorX = x;
                    cursorY = y;
                    break;
                }
            }
        }
    }
}

/**
 * Wyświetla aktualnego gracza, nazwę graczy oraz ich punkty.
 * @param board Przyjmuje tablicę z aktualnym stanem rozgrywki w celu policzenia punktów.
 */
void displayScore(int **board) {
    int p1_score = 0, p2_score = 0;
    char p1_score_str[2];
    char p2_score_str[2];
    char p1_output[26];
    char p2_output[26];

    for (i = 0; i < mapSizeInt; i++) {
        for (j = 0; j < mapSizeInt; j++) {
            if (board[i][j] == 1) {
                p1_score++;
            } else if (board[i][j] == 2) {
                p2_score++;
            }
        }
    }

    sprintf(p1_score_str, "%d", p1_score);
    sprintf(p2_score_str, "%d", p2_score);
    if (currentPlayer == 1) {
        snprintf(p1_output, sizeof p1_output, "-> %c %s score: %s", SYMBOL_1, player1_name, p1_score_str);
        snprintf(p2_output, sizeof p2_output, "  %c %s score: %s", SYMBOL_2, player2_name, p2_score_str);
    } else if (currentPlayer == 2) {
        snprintf(p1_output, sizeof p1_output, "  %c %s score: %s", SYMBOL_1, player1_name, p1_score_str);
        snprintf(p2_output, sizeof p2_output, "-> %c %s score: %s", SYMBOL_2, player2_name, p2_score_str);
    }
    printCentered(p1_output);
    printCentered(p2_output);
}

/**
 * Sprawdza bicie na północ od kursora.
 * Gdy sąsiednim pionkiem jest pionek przeciwnika, idzie dalej i szuka pierwszego własnego pionka. Gdy znajdzie, wraca do kursora i zamienia pionki na własne.
 * @return Zwraca 1 jeżeli istnieje możliwość bicia. 0 jeżeli możliwości nie ma w tym kierunku.
 */
int checkN() {
    int otherPlayerPiecesBetween = 0;
    int firstLoop = 0;
    for (i = cursorY - 1; i >= 0; i--, firstLoop++) {
        if ((reversiBoard[i][cursorX] == currentPlayer ||
             reversiBoard[i][cursorX] == 0) && firstLoop == 0) {
            return 0;
        } else if (reversiBoard[i][cursorX] != currentPlayer) {
            otherPlayerPiecesBetween++;
        }
        if (reversiBoard[i][cursorX] == currentPlayer &&
            otherPlayerPiecesBetween > 0) {
            for (j = i; j < cursorY; j++) {
                reversiBoard[j][cursorX] = currentPlayer;
            }
            return 1;
        }
    }
    return 0;
}

/**
 * Sprawdza bicie na północny-wschód od kursora.
 * Gdy sąsiednim pionkiem jest pionek przeciwnika, idzie dalej i szuka pierwszego własnego pionka. Gdy znajdzie, wraca do kursora i zamienia pionki na własne.
 * @return Zwraca 1 jeżeli istnieje możliwość bicia. 0 jeżeli możliwości nie ma w tym kierunku.
 */
int checkNE() {
    int otherPlayerPiecesBetween = 0;
    int firstLoop = 0;
    for (x = cursorX + 1, y = cursorY - 1; x < mapSizeInt && y >= 0; x++, y--, firstLoop++) {
        if ((reversiBoard[y][x] == currentPlayer ||
             reversiBoard[y][x] == 0) && firstLoop == 0) {
            return 0;
        } else if (reversiBoard[y][x] != currentPlayer) {
            otherPlayerPiecesBetween++;
        }
        if (reversiBoard[y][x] == currentPlayer &&
            otherPlayerPiecesBetween > 0) {
            for (i = x, j = y; i > cursorX && j < cursorY; i--, j++) {
                reversiBoard[j][i] = currentPlayer;
            }
            return 1;
        }
    }
    return 0;
}

/**
 * Sprawdza bicie na wschód od kursora.
 * Gdy sąsiednim pionkiem jest pionek przeciwnika, idzie dalej i szuka pierwszego własnego pionka. Gdy znajdzie, wraca do kursora i zamienia pionki na własne.
 * @return Zwraca 1 jeżeli istnieje możliwość bicia. 0 jeżeli możliwości nie ma w tym kierunku.
 */
int checkE() {
    int otherPlayerPiecesBetween = 0;
    int firstLoop = 0;
    for (i = cursorX + 1; i < mapSizeInt; i++, firstLoop++) {
        if ((reversiBoard[cursorY][i] == currentPlayer ||
             reversiBoard[cursorY][i] == 0) && firstLoop == 0) {
            return 0;
        }
        if (reversiBoard[cursorY][i] != currentPlayer) {
            otherPlayerPiecesBetween++;
        }
        if (reversiBoard[cursorY][i] == currentPlayer &&
            otherPlayerPiecesBetween > 0) {
            for (j = i; j > cursorX; j--) {
                reversiBoard[cursorY][j] = currentPlayer;
            }
            return 1;
        }
    }
    return 0;
}

/**
 * Sprawdza bicie na południowy-wschód od kursora.
 * Gdy sąsiednim pionkiem jest pionek przeciwnika, idzie dalej i szuka pierwszego własnego pionka. Gdy znajdzie, wraca do kursora i zamienia pionki na własne.
 * @return Zwraca 1 jeżeli istnieje możliwość bicia. 0 jeżeli możliwości nie ma w tym kierunku.
 */
int checkSE() {
    int otherPlayerPiecesBetween = 0;
    int firstLoop = 0;
    for (x = cursorX + 1, y = cursorY + 1; x < mapSizeInt && y < mapSizeInt; x++, y++, firstLoop++) {
        if ((reversiBoard[y][x] == currentPlayer ||
             reversiBoard[y][x] == 0) && firstLoop == 0) {
            return 0;
        }
        if (reversiBoard[y][x] != currentPlayer) {
            otherPlayerPiecesBetween++;
        }
        if (reversiBoard[y][x] == currentPlayer &&
            otherPlayerPiecesBetween > 0) {
            for (i = x, j = y; i > cursorX && j > cursorY; i--, j--) {
                reversiBoard[j][i] = currentPlayer;
            }
            return 1;
        }
    }
    return 0;
}

/**
 * Sprawdza bicie na południe od kursora.
 * Gdy sąsiednim pionkiem jest pionek przeciwnika, idzie dalej i szuka pierwszego własnego pionka. Gdy znajdzie, wraca do kursora i zamienia pionki na własne.
 * @return Zwraca 1 jeżeli istnieje możliwość bicia. 0 jeżeli możliwości nie ma w tym kierunku.
 */
int checkS() {
    int otherPlayerPiecesBetween = 0;
    int firstLoop = 0;
    for (i = cursorY + 1; i < mapSizeInt; i++, firstLoop++) {
        if ((reversiBoard[i][cursorX] == currentPlayer ||
             reversiBoard[i][cursorX] == 0) && firstLoop == 0) {
            return 0;
        }
        if (reversiBoard[i][cursorX] != currentPlayer) {
            otherPlayerPiecesBetween++;
        }
        if (reversiBoard[i][cursorX] == currentPlayer &&
            otherPlayerPiecesBetween > 0) {
            for (j = i; j > cursorY; j--) {
                reversiBoard[j][cursorX] = currentPlayer;
            }
            return 1;
        }
    }
    return 0;
}

/**
 * Sprawdza bicie na południowy-zachód od kursora.
 * Gdy sąsiednim pionkiem jest pionek przeciwnika, idzie dalej i szuka pierwszego własnego pionka. Gdy znajdzie, wraca do kursora i zamienia pionki na własne.
 * @return Zwraca 1 jeżeli istnieje możliwość bicia. 0 jeżeli możliwości nie ma w tym kierunku.
 */
int checkSW() {
    int otherPlayerPiecesBetween = 0;
    int firstLoop = 0;
    for (x = cursorX - 1, y = cursorY + 1; x >= 0 && y < mapSizeInt; x--, y++, firstLoop++) {
        if ((reversiBoard[y][x] == currentPlayer ||
             reversiBoard[y][x] == 0) && firstLoop == 0) {
            return 0;
        }
        if (reversiBoard[y][x] != currentPlayer) {
            otherPlayerPiecesBetween++;
        }
        if (reversiBoard[y][x] == currentPlayer &&
            otherPlayerPiecesBetween > 0) {
            for (i = x, j = y; i < cursorX && j > cursorY; i++, j--) {
                reversiBoard[j][i] = currentPlayer;
            }
            return 1;
        }
    }
    return 0;
}

/**
 * Sprawdza bicie na zachód od kursora.
 * Gdy sąsiednim pionkiem jest pionek przeciwnika, idzie dalej i szuka pierwszego własnego pionka. Gdy znajdzie, wraca do kursora i zamienia pionki na własne.
 * @return Zwraca 1 jeżeli istnieje możliwość bicia. 0 jeżeli możliwości nie ma w tym kierunku.
 */
int checkW() {
    int otherPlayerPiecesBetween = 0;
    int firstLoop = 0;
    for (i = cursorX - 1; i >= 0; i--, firstLoop++) {
        if ((reversiBoard[cursorY][i] == currentPlayer ||
             reversiBoard[cursorY][i] == 0) && firstLoop == 0) {
            return 0;
        }
        if (reversiBoard[cursorY][i] != currentPlayer) {
            otherPlayerPiecesBetween++;
        }
        if (reversiBoard[cursorY][i] == currentPlayer &&
            otherPlayerPiecesBetween > 0) {
            for (j = i; j < cursorX; j++) {
                reversiBoard[cursorY][j] = currentPlayer;
            }
            return 1;
        }
    }
    return 0;
}

/**
 * Sprawdza bicie na północny-zachód od kursora.
 * Gdy sąsiednim pionkiem jest pionek przeciwnika, idzie dalej i szuka pierwszego własnego pionka. Gdy znajdzie, wraca do kursora i zamienia pionki na własne.
 * @return Zwraca 1 jeżeli istnieje możliwość bicia. 0 jeżeli możliwości nie ma w tym kierunku.
 */
int checkNW() {
    int otherPlayerPiecesBetween = 0;
    int firstLoop = 0;
    for (x = cursorX - 1, y = cursorY - 1; x >= 0 && y >= 0; x--, y--, firstLoop++) {
        if ((reversiBoard[y][x] == currentPlayer ||
             reversiBoard[y][x] == 0) && firstLoop == 0) {
            return 0;
        }
        if (reversiBoard[y][x] != currentPlayer) {
            otherPlayerPiecesBetween++;
        }
        if (reversiBoard[y][x] == currentPlayer &&
            otherPlayerPiecesBetween > 0) {
            for (i = x, j = y; i < cursorX && j < cursorY; i++, j++) {
                reversiBoard[j][i] = currentPlayer;
            }
            return 1;
        }
    }
    return 0;
}

/**
 * Sprawdza czy istnieje możliwość jakiegokolwiek bicia.
 * @return Zwraca ilość kierunków w które zostały przeprowadzone bicia.
 */
int isInsertionAllowed() {
    // Contains in how many ways the move affects the board
    int correctMove = 0;

    if (checkN()) {
        correctMove++;
    }
    if (checkNE()) {
        correctMove++;
    }
    if (checkE()) {
        correctMove++;
    }
    if (checkSE()) {
        correctMove++;
    }
    if (checkS()) {
        correctMove++;
    }
    if (checkSW()) {
        correctMove++;
    }
    if (checkW()) {
        correctMove++;
    }
    if (checkNW()) {
        correctMove++;
    }

    return correctMove;
}

/**
 * Sprawdza czy na planszy jest jakiekolwiek miejsce na gre. W przeciwnym razie kończy grę.
 * @return
 */
int isBoardFull() {
    for (i = 0; i < mapSizeInt; i++) {
        for (j = 0; j < mapSizeInt; j++) {
            if (reversiBoard[i][j] == 0) {
                return 0;
            }
        }
    }
    printCentered("GAME OVER");
    return 1;
}

/**
 * Funkcja sprawdzając wolne pola na planszy oraz możliwość bicia w danym miejscu, decyduje czy ustawić kursor w nowym miejscu i zmienić gracza.
 *
 * {@see isBoardFull} {@see isInsertionAllowed}
 */
void insertPiece() {
    if (!isBoardFull() && isInsertionAllowed()) {
        reversiBoard[cursorY][cursorX] = currentPlayer;
        setCursor();
        if (currentPlayer == 1) {
            currentPlayer = 2;
        } else if (currentPlayer == 2) {
            currentPlayer = 1;
        }
    }
}

/**
 * Główna funkcja sterująca zachowaniem gry poprzez czytanie klawiszy wciśniętych przez gracza.
 *
 * Po rozpoczęciu gry tworzy potrzebne tablice, rysuje obszar gry na ekranie, wyświetla punkty i czeka na polecenia użytkownika.
 * Po skończeniu gry czyści pamięć po tablicach.
 */
void playReversi() {
    reversiBoard = initBoard();
    setCursor();
    reversiDrawableBoard = initDrawableBoard(reversiBoard);
    drawBoard(reversiDrawableBoard);
    displayScore(reversiBoard);
    char key;
    while ((key = readKey())) {
        switch (key) {
            case 'U': // Up
                moveUp(reversiBoard);
                break;
            case 'D': // Down
                moveDown(reversiBoard);
                break;
            case 'R': // Right
                moveRight(reversiBoard);
                break;
            case 'L': // Left
                moveLeft(reversiBoard);
                break;
            case 'E': // Enter
            case 'S': // Space
                insertPiece();
                break;
        }
        if (key == 'Q') {
            // Quit
            break;
        }
        reversiDrawableBoard = initDrawableBoard(reversiBoard);
        drawBoard(reversiDrawableBoard);
        displayScore(reversiBoard);
    }
    deleteBoard(reversiBoard);
    deleteDrawableBoard(reversiDrawableBoard);
}
