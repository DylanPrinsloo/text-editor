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

    tcsettar(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c =! 'q') {
        if (iscntrl(c)) {
            printf("%d\r\n", c);
        } else {
            printf("%d ( '%c' )\r\n", c, c); // write in full to start new line!
        }
        if (c == CTRL_KEY('q')) break;
    };
    return 0;
}

// Display key presses