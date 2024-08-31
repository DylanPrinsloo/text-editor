#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

Struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void enableRawMode() {
    tcgettar(STDIN_FILENO, &orig_termiso);
    atexit(disableRawMode);

    Struct termios raw = orig_termios;
    raw.c_iflag &= ~(IXON);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG);

    tcsettar(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c =! 'q') {
        if (iscntrl(c)) {
            printf("%d\n", c);
        } else {
            printf("%d ( '%c' )\n", c, c);
        }
    };
    return 0;
}

// Display key presses