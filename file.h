#define PREFIX "movies_"

char *create_dir()
{
  char num[6];
  sprintf(num, "%d", (rand() % 100000));
  char *dirname = calloc(23, sizeof(char));
  strcat(dirname, "moncadae.movies.");
  strcat(dirname, num);

  mkdir(dirname, 0750);

  return dirname;
}


void populate_dir(char *dir_name, struct movie *data)
{
  int *year_arr;
  int arr_size;
  year_arr = find_years(data, &arr_size);

  for (int i = 0; i < arr_size; i++)
  {
    struct movie *node = data;

    char filename[31] = {0};
    strcpy(filename, dir_name);
    strcat(filename, "/");
    char year_str[5];
    sprintf(year_str, "%d", year_arr[i]);
    strcat(filename, year_str);
    strcat(filename, ".txt");


    FILE *file = fopen(filename, "w");
    while (node != NULL)
    {
      if (node->year == year_arr[i])
      {
        fprintf(file, "%s\n", node->title);
      }
      node = node->next;
    }
    chmod(filename, 0640);
    fclose(file);
  }
  free(year_arr);
}


// Adapted from provided stat_example.c
void find_smallest_file(char *entryName)
{
  DIR *currDir = opendir(".");
  struct dirent *aDir;
  off_t file_size;
  struct stat dirStat;
  int i = 0;
  while ((aDir = readdir(currDir)) != NULL)
  {

    if (strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0)
    {
      // Get meta-data for the current entry
      stat(aDir->d_name, &dirStat);

      // check if current entry's size is smaller than the previously recorded smallest file
      if (i == 0 || dirStat.st_size < file_size)
      {
        file_size = dirStat.st_size;
        memset(entryName, '\0', sizeof(entryName));
        strcpy(entryName, aDir->d_name);
      }
      i++;
    }
  }
  closedir(currDir);
  return;
}


// Adapted from provided stat_example.c
void find_largest_file(char *entryName)
{
  DIR *currDir = opendir(".");
  struct dirent *aDir;
  off_t file_size;
  struct stat dirStat;
  int i = 0;
  while ((aDir = readdir(currDir)) != NULL)
  {
                                                              // needed to exclude excecutable, since it also matches with prefix
    if (strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0 && strcmp(aDir->d_name, "movies_by_year") != 0)
    {
      // Get meta-data for the current entry
      stat(aDir->d_name, &dirStat);

      // check if current entry's size is smaller than the previously recorded smallest file
      if (i == 0 || dirStat.st_size > file_size)
      {
        file_size = dirStat.st_size;
        memset(entryName, '\0', sizeof(entryName));
        strcpy(entryName, aDir->d_name);
      }
      i++;
    }
  }
  closedir(currDir);
  return;
}


void select_file()
{
  int choice = -1;

  while (choice)
  {
    printf("Which file you want to process?\n");
    printf("Enter 1 to pick the largest file\n");
    printf("Enter 2 to pick the smallest file\n");
    printf("Enter 3 to specify the name of a file\n\n");
    printf("Enter a choice from 1 to 3: ");
    scanf("%d", &choice);

    char filename[256];

    if (choice == 1)
    { // largest file
      find_largest_file(filename);
      struct movie *list = process_file(filename);

      if (list != NULL)
      {
        char *dirname = create_dir();
        printf("Created directory with name %s\n", dirname);
        populate_dir(dirname, list);
        free(dirname);
        free_list(list);
        break;
      }
      else
        choice = -1;
    }
    else if (choice == 2)
    { // smallest
      find_smallest_file(filename);
      struct movie *list = process_file(filename);

      if (list != NULL)
      {
        char *dirname = create_dir();
        printf("Created directory with name %s\n", dirname);
        populate_dir(dirname, list);
        free(dirname);
        free_list(list);
        break;
      }
      else
        choice = -1;
    }
    else if (choice == 3)
    { // specify filename
      printf("Enter the complete filename: ");
      char input[256] = {};
      scanf("%s", &filename);
      struct movie *list = process_file(filename);

      if (list != NULL)
      {
        char *dirname = create_dir();
        printf("Created directory with name %s\n", dirname);
        populate_dir(dirname, list);
        free(dirname);
        free_list(list);
        break;
      }
      else
        choice = -1;
    }
    else
    {
      printf("Invalid input, please try again.\n");
      choice = -1;
    }
  }
}
