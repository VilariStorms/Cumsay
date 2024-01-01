#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "cum.h"
// ngl I forgot to update this for a while and I'm too lazy to check what
// version it's on so I'm just gonna say it's 0.1.5
#define VERSION "0.1.5"

// pretty horrid code but it's talking cum ffs I cant be arsed to make it pretty
// should've used rust tbh - deltara

char *current_colour = NULL;
int rainbowed = 0;

static valid_colours colours = { .red = "\x1b[31m",
				 .green = "\x1b[32m",
				 .yellow = "\x1b[33m",
				 .blue = "\x1b[34m",
				 .magenta = "\x1b[35m",
				 .cyan = "\x1b[36m",
				 .white = "\x1b[37m" };

argument help = { .long_arg = "--help",
		  .short_arg = "-h",
		  .takes_arg = 0,
		  .handler = print_help };
argument version = { .long_arg = "--version",
		     .short_arg = "-v",
		     .takes_arg = 0,
		     .handler = print_version };
argument colour = { .long_arg = "--colour",
		    .short_arg = "-c",
		    .takes_arg = 1,
		    .handler = set_colour };
argument rainbow = { .long_arg = "--rainbow",
		     .short_arg = "-r",
		     .takes_arg = 0,
		     .handler = set_rainbow };

static argument *arguments[] = { &help, &version, &colour, &rainbow };
static int num_args = sizeof(arguments) / sizeof(arguments[0]);

static char *top = "/‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒\\\n"
                   "|                                        |\n";
static char *bottom = 
                   "|                                        |\n"
		      "\\‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒/ \n";
static char *sperm = "                ____     _/ \n"
		     "______     ___.'  o `.  / \n"
		     "/~----,\\___/,--.   ,_ | \n"
		     "        `-----'   `---' ";

void cum_say(char *message, char *colour, int rainbow, int message_size)
{
	if (colour != NULL) {
		printf("%s", colour);
	} else if (rainbow) {
		random_colour();
	}
	printf("%s", top);
	char tmp[69] = { 0 };
	int count = 0;
	for (int i = 0; i < message_size; i++) {
		if (count == 34) {
			if (rainbow)
				random_colour();
			printf("|   %3s   |\n", tmp);
			count = 0;
			memset(tmp, 0, 69);
		}
		// check if it's a printable character 
		if ((message[i] < 32) || (message[i] > 126))
			continue;
		tmp[count] = message[i];
		count++;
	}
	/* this is horrible but it's 4am and it works so idrc */
	if (count > 0) {
		if (rainbow)
			random_colour();
		int str = 34 - strlen(tmp);
		int i;
		for (i = 0; i < str; i++) {
			strcat(tmp, " ");
		}
		printf("|   %3s   |\n", tmp);	
	
	}

	if (rainbow)
		random_colour();
	printf("%s\n", bottom);
	if (rainbow)
		random_colour();
	printf("%s\n", sperm);
	printf("\x1b[0m");
}

int parse_args(char *arg, char *argstr, int *ii)
{
	for (int i = 0; i < num_args; i++) {
		if (strcmp(arg, arguments[i]->long_arg) == 0 ||
		    strcmp(arg, arguments[i]->short_arg) == 0) {
			arguments[i]->handler(argstr);
			if ((argstr != NULL) && arguments[i]->takes_arg)
				*ii += 1;
			return 0;
		}
	}
	return -1;
}

int main(int argc, char *argv[])
{
	char *message;
	size_t message_size = 1;
	srand(time(NULL));
	message = calloc(sizeof(char), message_size);
	for (int i = 1; i < argc; i++) {
		char *argstr = NULL;
		switch (argv[i][0]) {
		case '-':
			if ((argc - i) >= 1)
				argstr = argv[i + 1];

			if (parse_args(argv[i], argstr, &i) != -1) {
				continue;
			} else {
				message_size += strlen(argv[i]) + 1;
				char *tmp = realloc(message, message_size);
				if (tmp == NULL) {
					printf("Error: realloc failed\n");
					exit(1);
				}
				message = tmp;
				strcat(message, argv[i]);
				strcat(message, " ");
			}
			break;
		default:
			message_size += strlen(argv[i]) + 1;
			char *tmp = realloc(message, message_size);
			if (tmp == NULL) {
				printf("Error: realloc failed\n");
				exit(1);
			}
			message = tmp;
			strcat(message, argv[i]);
			strcat(message, " ");

			break;
		}
	}
	/* handle piped input */
	if (!isatty(STDIN_FILENO)) {
		char *tmp = realloc(message, message_size + 1);
		if (tmp == NULL) {
			printf("Error: realloc failed\n");
			exit(1);
		}
		message = tmp;
		strcat(message, "\n");
		char *line = NULL;
		size_t len = 0;
		ssize_t read;
		while ((read = getline(&line, &len, stdin)) != -1) {
			message_size += strlen(line) + 1;
			tmp = realloc(message, message_size);
			if (tmp == NULL) {
				printf("Error: realloc failed\n");
				exit(1);
			}
			message = tmp;
			strcat(message, line);
		}
		free(line);
	}
	if (message_size == 1)
		print_help(NULL);
	cum_say(message, current_colour, rainbowed, message_size);
}

int print_help(char *arg)
{
	printf("Usage: cum [OPTION]... [MESSAGE]\n"
	       "Ejaculate a message!\n\n"
	       "  -c, --colour=COLOUR\t\tSet the colour of the message\n"
	       "  -r, --rainbow\t\t\tSet the colour of the message to a random colour\n"
	       "  -h, --help\t\t\tPrint this help message and exit\n"
	       "  -v, --version\t\t\tPrint the version number and exit\n\n"
	       "Valid colours are: red, green, yellow, blue, magenta, cyan, white\n\n"
	       "Report bugs to <@deltara3> on Discord.\n");
	exit(0);
	return 0;
}
int print_version(char *arg)
{
	printf("cum version %s\n", VERSION);
	exit(0);
	return 0;
}

int set_rainbow(char *arg)
{
	rainbowed = 1;
	return 0;
}
int set_colour(char *colour)
{
	if (colour == NULL) {
		printf("No colour specified\n");
		exit(1);
	}
	if ((strcmp(colour, "red") == 0) || strcmp(colour, "r") == 0) {
		current_colour = colours.red;
	} else if ((strcmp(colour, "green") == 0) || strcmp(colour, "g") == 0) {
		current_colour = colours.green;
	} else if ((strcmp(colour, "yellow") == 0) ||
		   strcmp(colour, "y") == 0) {
		current_colour = colours.yellow;
	} else if ((strcmp(colour, "blue") == 0) || strcmp(colour, "b") == 0) {
		current_colour = colours.blue;
	} else if ((strcmp(colour, "magenta") == 0) ||
		   strcmp(colour, "m") == 0) {
		current_colour = colours.magenta;
	} else if ((strcmp(colour, "cyan") == 0) || strcmp(colour, "c") == 0) {
		current_colour = colours.cyan;
	} else if ((strcmp(colour, "white") == 0) || strcmp(colour, "w") == 0) {
		current_colour = colours.white;
	} else {
		printf("Invalid colour: %s\n", colour);
		exit(1);
	}
	return 0;
}

void random_colour()
{
	int r = rand() % 7;
	switch (r) {
	case 0:
		printf("%s", colours.red);
		break;
	case 1:
		printf("%s", colours.green);
		break;
	case 2:
		printf("%s", colours.yellow);
		break;
	case 3:
		printf("%s", colours.blue);
		break;
	case 4:
		printf("%s", colours.magenta);
		break;
	case 5:
		printf("%s", colours.cyan);
		break;
	case 6:
		printf("%s", colours.white);
		break;
	default:
		printf("%s", colours.white);
		break;
	}
}
