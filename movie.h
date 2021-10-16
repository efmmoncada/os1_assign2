struct movie
{
  char *title;
  short year;
  short num_lang;
  char **languages;
  double rating;
  struct movie *next;
};

/* Parse the current line which is comma delimited and create a
*  movie struct with the data in this line
*  Adapted from resource code provided in assignment.
*  Adapted on 9/24/21
*/
struct movie *create_movie(char *currLine)
{
  struct movie *currmovie = malloc(sizeof(struct movie));
  // For use with strtok_r
  char *saveptr;

  // The first token is the title
  char *token = strtok_r(currLine, ",", &saveptr);
  currmovie->title = calloc(strlen(token) + 1, sizeof(char));
  strcpy(currmovie->title, token);

  // The next token is the year
  token = strtok_r(NULL, ",", &saveptr);
  currmovie->year = atoi(token);

  // The next token is the languages // how to handle this, since its a pointer to array.
  token = strtok_r(NULL, ",", &saveptr);
  // gets rid of brackets
  token++;
  token[strlen(token) - 1] = '\0';

  char *str = token;

  int num_lang = 1;
  for (int i = 0; i < strlen(str); i++)
  {
    if (str[i] == ';')
      num_lang++;
  }
  currmovie->num_lang = num_lang;

  currmovie->languages = calloc(currmovie->num_lang, sizeof(char *));

  char *indiv_lang = strtok(str, ";");

  int i = 0;
  while (indiv_lang != NULL)
  {
    currmovie->languages[i] = calloc(strlen(indiv_lang) + 1, sizeof(char));
    strcpy(currmovie->languages[i], indiv_lang);
    indiv_lang = strtok(NULL, ";");
    i++;
  }

  // The last token is the rating
  token = strtok_r(NULL, "\n", &saveptr);
  currmovie->rating = strtod(token, NULL);

  // Set the next node to NULL in the newly created movie entry
  currmovie->next = NULL;

  return currmovie;
}

/*
* Return a linked list of movies by parsing data from
* each line of the specified file.
* Adapted from resource code provided in assignment.
* Adapted on 9/24/21
*/
struct movie *process_file(char *file_path)
{
  // Open the specified file for reading only
  FILE *movie_file = fopen(file_path, "r");
  if (movie_file == NULL) {
    printf("The file %s was not found. Try again.\n\n", file_path);
    return NULL;
  }

  char *currLine = NULL;
  size_t len = 0;
  ssize_t nread;
  char *token;

  // The head of the linked list
  struct movie *head = NULL;
  // The tail of the linked list
  struct movie *tail = NULL;

  int flag = 1;
  int num_movies = 0;

  // Read the file line by line
  while ((nread = getline(&currLine, &len, movie_file)) != -1)
  {
    // skips the first "row" which contains labels, not actual data.
    if (flag == 1)
    {
      flag = 0;
      continue;
    }
    // Get a new movie node corresponding to the current line
    struct movie *newNode = create_movie(currLine);

    // Is this the first node in the linked list?
    if (head == NULL)
    {
      // This is the first node in the linked link
      // Set the head and the tail to this node
      head = newNode;
      tail = newNode;
    }
    else
    {
      // This is not the first node.
      // Add this node to the list and advance the tail
      tail->next = newNode;
      tail = newNode;
    }
    num_movies++;
  }
  free(currLine);
  fclose(movie_file);
  return head;
}

// void print_top_movies(struct movie **movie_arr, int arr_size)
// {
//   for (int i = 0; i < arr_size; i++)
//   {
//     printf("%d %.1f %s\n", movie_arr[i]->year, movie_arr[i]->rating, movie_arr[i]->title);
//   }
// }

/* Design: create an array of movies. For all movies, check if array contains a movie with the same year as the curr movie.
* if it does, check ratings, and replace if higher. if you get to the end of the array and no movie in the array matches the
* curr movies year, append that movie to the array. Will likey need to keep track of the arrays size in order to use an inner for loop
* within the outer while loop to iterate over the linked list of movies
* finally, print the array at the end */
int *find_years(struct movie *node, int* arr_size)
{


  int *year_arr = calloc(1, sizeof(int));
  *arr_size = 1;
  int flag = 0;

  year_arr[0] = node->year;

  while (node != NULL)
  {
    for (int i = 0; i < *arr_size; i++)
    {
      if (year_arr[i] != node->year)
        continue;
      else
        flag = 1;
    }

    if (flag == 0)
    { // if the movie's year has not been seen, add it to the array
      year_arr = realloc(year_arr, (*arr_size + 1) * sizeof(int));
      year_arr[*arr_size] = node->year;
      (*arr_size)++;
    }

    node = node->next;
    flag = 0;
  }

  //print_top_movies(top_movies, arr_size);
  return year_arr;
}

void free_list(struct movie *node)
{
  struct movie *temp = NULL;
  while (node != NULL)
  {
    temp = node->next;
    free(node->title);
    for (int i = 0; i < node->num_lang; i++)
    {
      free(node->languages[i]);
    }
    free(node->languages);
    free(node);
    node = temp;
  }
}
