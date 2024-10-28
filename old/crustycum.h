// Contents: header file for cum.c

// struct for colours
typedef struct {
	char *red;
	char *green;
	char *yellow;
	char *blue;
	char *magenta;
	char *cyan;
	char *white;
	char *reset;
} valid_colours;

// struct for args
typedef struct {
	char *long_arg;
	char *short_arg;
	int takes_arg;
	int (*handler)(char *arg);
} argument;

// functions
int print_help(char *useless);
int print_version(char *useless);
int set_colour(char *colour);
int set_rainbow (char *string);
void random_colour();

