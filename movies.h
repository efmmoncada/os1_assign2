
char *select_file() {

  int choice = -1;

  while (choice) {
    printf("Which file you want to process?\n");
    printf("Enter 1 to pick the largest file\n");
    printf("Enter 2 to pick the smallest file\n");
    printf("Enter 3 to specify the name of a file\n\n");
    printf("Enter a choice from 1 to 3: ");


    scanf("%d", &choice);


    if (choice == 1) {                      // largest file
      printf("selected largest file\n");
      break;
    } else if (choice == 2) {               // smallest
      printf("selected smallest file\n");
      break;
    } else if (choice == 3) {               // filename
      printf("selected manual entry\n");
      break;
    } else {
      printf("Invalid input, please try again.\n");
      choice = -1;
    }
  }



  char* dir;
  return dir;
}
