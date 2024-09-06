/*** Includes ***/

#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>

/*** defines ***/
// #define CTRL_KEY(k) ((k) & 0x1f)

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
     raw/c_oflag &= ~(CS8); // add CS ------------!
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    // Ctrl-V == 22 byte && Ctrl-0 == 15 byte
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if (tcsettar(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

/*** init ***/

int main() {
    enableRawMode();

    while (1) {
        char c = '\0';
        if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) die("read");
        if (iscntrl(c)) {
        printf("%d\r\n", c);
        } else {
        printf("%d ('%c')\r\n", c, c);
        }
        if (c == 'q') break;
    }

    return 0;
}
