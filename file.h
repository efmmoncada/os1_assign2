
char* create_dir() {
  char num[6];
  sprintf(num, "%d", (rand() % 100000));
  char* dirname = calloc(23, sizeof(char));
  strcat(dirname, "moncadae.movies.");
  strcat(dirname, num);

  mkdir(dirname, 0750);

  return dirname;
}

void populate_dir(char* dir_name, struct movie* data) {
  int *year_arr;
  int arr_size;
  year_arr = find_years(data, &arr_size);
  printf("%d\n", year_arr[0]);


}


void select_file() {

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
      //
      break;
    } else if (choice == 2) {               // smallest
      printf("selected smallest file\n");
      break;
    } else if (choice == 3) {               // filename
      printf("Enter the complete filename: ");
      char input[256] = {};
      scanf("%s", &input);
      printf("Now processing the chosen file named %s\n", input);
      struct movie* list = process_file(input);
      if (list != NULL) {
        char *dirname = create_dir();
        printf("Created directory with name %s\n", dirname);
        populate_dir(dirname, list);
        free(dirname);
        break;
      } else choice = -1;

    } else {
      printf("Invalid input, please try again.\n");
      choice = -1;
    }
  }
}
