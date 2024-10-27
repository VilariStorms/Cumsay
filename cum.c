#include <stdio.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/ioctl.h>
#endif

#include "cum.h"

int get_term_width(void) {
    // For fuck's sake Microsoft
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
            return -1;

        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #else
        struct winsize w;

        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
            return -1;

        return w.ws_col;
    #endif
}

int main(void) {


    return 0;
}
