#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define CTRL_KEY(k) ((k) & 0x1f)

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON | ISIG);
    raw.c_iflag &= ~(IXON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void editorProcessKeypress() {
    char c = '\0';
    read(STDIN_FILENO, &c, 1);

    switch (c) {
        case CTRL_KEY('q'):
            exit(0);
            break;
    }
}

void editorRefreshScreen() {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

int main() {
    enableRawMode();

    while (1) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}
