#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "cum.h"
// ngl I forgot to update this for a while and I'm too lazy to check what
// version it's on so I'm just gonna say it's 0.1.3
#define VERSION "0.1.3"

// pretty horrid code but it's talking cum ffs I cant be arsed to make it pretty
//  should've used rust tbh - deltara
valid_colours colours = { .red = "\x1b[31m",
			  .green = "\x1b[32m",
			  .yellow = "\x1b[33m",
			  .blue = "\x1b[34m",
			  .magenta = "\x1b[35m",
			  .cyan = "\x1b[36m",
			  .white = "\x1b[37m" };

char arguments[][69] = { "-h", "--help",   "-v", "--version",
			 "-c", "--colour", "-r", "--rainbow" };

char *top = "/‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒\\\n\n";
char *cum = "\n"
	    "\\‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒/ \n"
	    "                ____     _/ \n"
	    "______     ___.'  o `.  / \n"
	    "/~----,\\___/,--.   ,_ | \n"
	    "        `-----'   `---' ";

void cum_say(char *message, char *colour, int rainbow)
{
	if (colour != NULL) {
		printf("%s", colour);
	}
	if (rainbow == 1) {
		random_colour();
	}
	printf("%s", top);

	char *token = strtok(message, "\n");
	while (token != NULL) {
		if (rainbow) {
			random_colour();
		}
		printf("%22s\n", token);
		token = strtok(NULL, "\n");
	}

	printf("%s\n", cum);
	printf("\x1b[0m");
}

int main(int argc, char *argv[])
{
	srand(time(NULL)); // for random colour
	char *colour = NULL;
	char *message;
	int rainbow = 0;
	size_t message_size = 1;

	message = calloc(sizeof(char), 1);

	if (argc >= 1) {
		for (int i = 1; i < argc; i++) {
			switch (argv[i][0]) {
			case '-':
				if (validate_arg(argv[i], &rainbow) &&
				    lenght_check(argc, i)) {
					parse_colour(argv[i + 1], &colour);
					i++;
					break;
				}
				if (rainbow) {
					break;
				}

			default:
				message_size += strlen(argv[i]) + 2;
				message = realloc(
					message, (sizeof(char) * message_size));
				if (message == NULL) {
					fprintf(stderr,
						"Error allocating memory \n");
					return 1;
				}
				strcat(message, argv[i]);
				strcat(message, " ");
				break;
			}
		}
	}

	// Handle piped input
	if (!isatty(STDIN_FILENO)) {
		char *line = NULL;
		size_t buffer_size = 0;
		ssize_t line_size;
		while ((line_size = getline(&line, &buffer_size, stdin)) !=
		       -1) {
			message = realloc(message,
					  sizeof(char) * (1 + strlen(message) +
							  line_size));
			strcat(message, line);
		}
		free(line);
		// If no piped input and no arguments then error
	} else if (argc == 1) {
		fprintf(stderr, "Usage: cumsay <text_to_ejaculate> \n");
		return 1;
	}

	// Ejaculate
	cum_say(message, colour, rainbow);
	return 0;
	// no need to free message as it is freed when the program exits :D
}

// The horrible stuff below

void print_version()
{
	printf("cumsay version %s \n", VERSION);
}

void print_help()
{
	printf("Usage: cumsay <text_to_ejaculate> \n");
	printf("Options: \n");
	printf("  -h, --help     Show this help message and exit \n");
	printf("  -v, --version  Show version number and exit \n");
	printf("  -c, --colour   Change the colour of the cum \n");
	printf("  -r, --rainbow  Make the cum rainbow \n");
}

int lenght_check(int argc, int arg_index)
{
	if (arg_index + 1 >= argc) {
		fprintf(stderr, "No colour specified \n");
		exit(1);
	}
	return 1;
}
int validate_arg(char *arg, int *rainbow)
{
	// parse arguments and check if they are valid
	// -h, --help, -v, --version, -c, --colour, -r, --rainbow
	if (strcmp(arg, arguments[0]) == 0 || strcmp(arg, arguments[1]) == 0) {
		print_help(); // help
		exit(0);
	}
	if (strcmp(arg, arguments[2]) == 0 || strcmp(arg, arguments[3]) == 0) {
		print_version(); // version
		exit(0);
	}

	if (strcmp(arg, arguments[6]) == 0 || strcmp(arg, arguments[7]) == 0) {
		(*rainbow) = 1; // rainbow
		return 0;
	}
	if (strcmp(arg, arguments[4]) == 0 || strcmp(arg, arguments[5]) == 0) {
		return 1;
		// colour
	}

	// not a valid argument, must be text
	return 0;
}

int parse_colour(char *arg, char **colour)
{
	int i = 0;
	if (arg[0] == '-') {
		i = 1;
	}
	switch (arg[i]) {
	case 'r':
		*colour = colours.red;
		break;
	case 'g':
		*colour = colours.green;
		break;
	case 'y':
		*colour = colours.yellow;
		break;
	case 'b':
		*colour = colours.blue;
		break;
	case 'm':
		*colour = colours.magenta;
		break;
	case 'c':
		*colour = colours.cyan;
		break;
	case 'w':
		*colour = colours.white;
		break;
	default:
		fprintf(stderr, "Invalid colour: %s \n", arg);
		exit(1);
	}
	return 0;
}
void random_colour()
{
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
