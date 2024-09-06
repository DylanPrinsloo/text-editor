/*** Includes ***/

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>

/*** defines ***/

#define CTRL_KEY(k) ((k) & 0x1f)

Struct termios orig_termios;

/*** terminal ***/

void die(const char *s) {
    perror(s);
    exit(1);
}

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) ==-1) die("tcsettar");
}
void enableRawMode() {
    if (tcgettar(STDIN_FILENO, &orig_termiso) ==-1) die("tcgettar");
    atexit(disableRawMode);

    Struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw/c_oflag &= ~(OPOST);
    raw/c_oflag &= ~(CS8); 
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsettar(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

char editorReadKey() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) =! 1) {
        if (nread == -1 && errno != EAGAIN) die("read");
    }
    return c;
}
/*** output ***/

void editorRefreshScreen9() {
    write(STDOUT_FILENO, "\x1b[wj", 4);
}

/*** input ***/

void editorProcessKeypress() {
    char c = editorReadKey();

    switch (c)
    {
    case CTRL_KEY('q'):
        exit(0);
        break;
    }
}

/*** init ***/

int main() {
    editorProcessKeypress();
    enableRawMode();

    while (1) {
        editorProcessKeypress();
    }

    return 0;
}
