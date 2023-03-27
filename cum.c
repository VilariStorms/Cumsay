#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//pretty horrid code but it's talking cum ffs I cant be arsed to make it pretty

void cum_say(char *message) {
    char *cum = "\n"
    "\\‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒/ \n"
    "                ____     _/ \n"
    "______     ___.'  o `.  / \n"
    "/~----,\\___/,--.   ,_ | \n"
    "        `-----'   `---' ";
    printf("/‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒\\ \x1b[3m \n\n");
    printf("%22s \n", message);
    printf("\x1b[0m %s \n", cum);
}

int main(int argc, char *argv[]) {
    char *message;
    if (argc > 1) {
        size_t message_size = 0;
        for (int i = 1; i < argc; i++) {
            message_size += strlen(argv[i]) + 1; 
        }
        message = malloc(message_size * sizeof(char));
        message[0] = '\0'; 
        for (int i = 1; i < argc; i++) {
            strcat(message, argv[i]);
            if (i < argc - 1) strcat(message, " "); 
        }


    } else {
        if (!isatty(STDIN_FILENO)) {
            size_t buffer_size = 256;
            message = malloc(buffer_size * sizeof(char));
            message[0] = '\0'; 
            char *line = NULL;
            ssize_t line_size;
            while ((line_size = getline(&line, &buffer_size, stdin)) != -1) {
                message = realloc(message, (strlen(message) + line_size + 1) * sizeof(char));
                strcat(message, line);
            }
            free(line);  
        
        
        }else {
            fprintf(stderr, "Usage cumsay <text_to_ejaculate> \n");
            return 1;
    }
    }
    cum_say(message);
    return 0;
}
