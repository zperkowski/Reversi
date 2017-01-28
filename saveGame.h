#include "stdio.h"
#include "string.h"
#include "unistd.h"

extern char player1_name[];
extern char player2_name[];
extern char *fileName;

void saveToFile() {
  FILE *file;
  file = fopen(fileName, "w");
  fprintf(file, "%s\n%s", player1_name, player2_name);
  fclose(file);
}

void readFromFile() {
  FILE *file;
  file = fopen(fileName, "r");
  fscanf(file, "%s", player1_name);
  fscanf(file, "%s", player2_name);
  fclose(file);
}

int testFile() {
  if(access(fileName, F_OK) != -1) {
      // file exists
      readFromFile();
  } else {
      // file doesn't exist
      saveToFile();
  }
  return 0;
}
