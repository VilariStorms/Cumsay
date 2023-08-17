#include "cum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// ngl I forgot to update this for a while and I'm too lazy to check what
// version it's on so I'm just gonna say it's 0.1.3
#define VERSION "0.1.3"

// pretty horrid code but it's talking cum ffs I cant be arsed to make it pretty
//  should've used rust tbh - deltara
valid_colours colours = {.red = "\x1b[31m",
                         .green = "\x1b[32m",
                         .yellow = "\x1b[33m",
                         .blue = "\x1b[34m",
                         .magenta = "\x1b[35m",
                         .cyan = "\x1b[36m",
                         .white = "\x1b[37m"};

char arguments[][69] = {"-h", "--help",   "-v", "--version",
                        "-c", "--colour", "-r", "--rainbow"};

void cum_say(char *message, char *colour, int rainbow) {
  if (colour != NULL) {
    printf("%s", colour);
  }

  char *cum =
      "\n"
      "\\‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒/ \n"
      "                ____     _/ \n"
      "______     ___.'  o `.  / \n"
      "/~----,\\___/,--.   ,_ | \n"
      "        `-----'   `---' ";
  if (rainbow == 1) {
    char *token = strtok(message, "\n");
    random_colour();
    printf("/‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒\\ \x1b[3m \n\n");
    while (token != NULL) {
      printf("%22s \n", token);
      random_colour();
      token = strtok(NULL, "\n");
    }
  } else {
    printf("/‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒\\ \x1b[3m \n\n");
    printf("%22s\n", message);
  }

  printf("%s \n", cum);
  printf("\x1b[0m");
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  char *colour = NULL;
  char *message;
  int rainbow = 0;
  size_t message_size = 0;
  message = calloc(sizeof(char), 1);
  int arg;
  int valid_arg = 0;

  if (argc >= 1) {
    for (int i = 1; i < argc; i++) {
      arg = validate_arg(argv[i]);
      switch (arg) {
        case 0:
          message_size += strlen(argv[i]) + 1;
          message = realloc(message, sizeof(char) * message_size);
          strcat(message, argv[i]);
          strcat(message, " ");
          valid_arg += 1;
          break;
        case 1:  // help
          print_help();
          return 0;
        case 2:  // version
          print_version();
          return 0;
        case 3:  // colour
          // check if next argument is a proper colour but first check if there
          // is another element in argv
          if (i + 1 >= argc) {
            fprintf(stderr, "Error: no colour specified \n");
            return 1;
          }
          parse_colour(argv[i + 1], &colour);
          i++;
          break;
        case 4:  // rainbow
          rainbow = 1;
          break;
      }
    }
  }

  // Handle piped input
  if (!isatty(STDIN_FILENO)) {
    char *line = NULL;
    size_t buffer_size = 0;
    ssize_t line_size;
    while ((line_size = getline(&line, &buffer_size, stdin)) != -1) {
      message =
          realloc(message, sizeof(char) * (1 + strlen(message) + line_size));
      strcat(message, line);
    }
    free(line);
    // If no piped input and no arguments then error
  } else if (valid_arg == 0) {
    fprintf(stderr, "Usage: cumsay <text_to_ejaculate> \n");
    return 1;
  }

  // Ejaculate
  cum_say(message, colour, rainbow);
  return 0;
  // no need to free message as it is freed when the program exits :D
}

// The horrible stuff below

void print_version() { printf("cumsay version %s \n", VERSION); }
void print_help() {
  printf("Usage: cumsay <text_to_ejaculate> \n");
  printf("Options: \n");
  printf("  -h, --help     Show this help message and exit \n");
  printf("  -v, --version  Show version number and exit \n");
  printf("  -c, --colour   Change the colour of the cum \n");
  printf("  -r, --rainbow  Make the cum rainbow \n");
}

int parse_colour(char *arg, char **colour) {
  // TODO: add more colours and handle misspelt colours
  if (strcmp(arg, "red") == 0) {
    *colour = colours.red;
  } else if (strcmp(arg, "green") == 0) {
    *colour = colours.green;
  } else if (strcmp(arg, "yellow") == 0) {
    *colour = colours.yellow;
  } else if (strcmp(arg, "blue") == 0) {
    *colour = colours.blue;
  } else if (strcmp(arg, "magenta") == 0) {
    *colour = colours.magenta;
  } else if (strcmp(arg, "cyan") == 0) {
    *colour = colours.cyan;
  } else if (strcmp(arg, "white") == 0) {
    *colour = colours.white;
  } else {
    fprintf(stderr, "Invalid colour: %s \n", arg);
    return 1;
  }
  return 0;
}

// Not really necessary but it keeps main() clean
int validate_arg(char *arg) {
  // parse arguments and check if they are valid
  // -h, --help, -v, --version, -c, --colour, -r, --rainbow
  if (strcmp(arg, arguments[0]) == 0 || strcmp(arg, arguments[1]) == 0) {
    return 1;  // help
  } else if (strcmp(arg, arguments[2]) == 0 || strcmp(arg, arguments[3]) == 0) {
    return 2;  // version
  } else if (strcmp(arg, arguments[4]) == 0 || strcmp(arg, arguments[5]) == 0) {
    // change colour
    return 3;
  } else if (strcmp(arg, arguments[6]) == 0 || strcmp(arg, arguments[7]) == 0) {
    // rainbow
    return 4;
  }
  // not a valid argument, must be text
  return 0;
}

void random_colour() {
  // changes the terminal text colour to a random colour
  // Note this is horrible but ehh who cares, it works and it's not like this is
  // a serious project
  int randomIndex = rand() % 7;
  const char *randomColor = NULL;
  switch (randomIndex) {
    case 0:
      randomColor = colours.red;
      break;
    case 1:
      randomColor = colours.green;
      break;
    case 2:
      randomColor = colours.yellow;
      break;
    case 3:
      randomColor = colours.blue;
      break;
    case 4:
      randomColor = colours.magenta;
      break;
    case 5:
      randomColor = colours.cyan;
      break;
    case 6:
      randomColor = colours.white;
      break;
  }
  printf("%s", randomColor);
}
