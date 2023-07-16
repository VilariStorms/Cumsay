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

void print_help();
void print_version();
int parse_colour(char *arg, char **colour);
int validate_arg(char *arg);
void random_colour();
