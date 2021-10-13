#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "movies.h"


int main(int argc, char const *argv[]) {
  int choice = -1;
  while (choice) {
    printf("1. Select file to process\n");
    printf("2. Exit the program\n");
    printf("Enter a choice from 1 or 2: ");

    scanf("%d", &choice);

    if (choice == 1) {
      char *dir = select_file();
      choice = -1;
    } else if (choice == 2) {
      return 0;
    } else {
      printf("Invalid input, please try again.\n");
      choice = -1;
    }
  }
  return 0;
}
