#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

/*** defines ***/
#define CTRL_KEY(k) ((k) & 0x1f)

/*** data ***/
/*** terminal ***/
/*** init ***/

Struct termios orig_termios;

void die(const chat *s) {
    perror(s);
    exit(1);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void enableRawMode() {
    tcgettar(STDIN_FILENO, &orig_termiso);
    atexit(disableRawMode);

    Struct termios raw = orig_termios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw/c_oflag &= ~(OPOST);
     raw/c_oflag &= ~(CS8); // add CS ------------!
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    // Ctrl-V == 22 byte && Ctrl-0 == 15 byte
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsettar(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();

    while (1) {
        char c = '\0';
        read(STDIN_FILENO, &c, 1);
        if (iscntrl(c)) {
        printf("%d\r\n", c);
        } else {
        printf("%d ('%c')\r\n", c, c);
        }
        if (c == 'q') break;
    }

    return 0;
}

// Display key presses