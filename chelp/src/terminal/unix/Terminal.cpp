#include "Terminal.h"


Terminal::Terminal(int min_col, int min_row) : min_col(min_col), min_row(min_row) {
    enableRawMode();
    checkSize();
    clearScreen();
}

Terminal::~Terminal() {
    disableRawMode();
}

void Terminal::enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;

    raw.c_lflag &= ~(ECHO | ICANON | ISIG); // disable echo and signals
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void Terminal::disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void Terminal::checkSize() {
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    if (ws.ws_col < min_col || ws.ws_row < min_row) {
        std::cerr << "Terminal size is too small. Minimum: " << min_col << "x" << min_row << std::endl;
        exit(1);
    }
}

int Terminal::getKey() {
        char ch;
        if (read(STDIN_FILENO, &ch, 1) == 1) {
            if (ch == KEY_ESCAPE) {
                fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
                char next;
                usleep(10000); // timeot (10 ms)
                if (read(STDIN_FILENO, &next, 1) == 1) {
                    if (next == '[') {
                        char arrow;
                        if (read(STDIN_FILENO, &arrow, 1) == 1) {
                            if (arrow == 'A') return KEY_UP;
                            if (arrow == 'B') return KEY_DOWN;
                            if (arrow == 'C') return KEY_RIGHT;
                            if (arrow == 'D') return KEY_LEFT;
                        }
                    }
                }
                fcntl(STDIN_FILENO, F_SETFL, 0);
                return KEY_ESCAPE;
            }
            return ch;
        }
        return KEY_NONE;
    }

void Terminal::draw( int line,  int col,  char ch,  int effect) {
    printf("\033[%d;%dH", line, col); // move cursor

    // setup effects
    if (effect == bold) printf("\033[1m");
    if (effect == dim) printf("\033[2m");
    if (effect == italic) printf("\033[3m");
    if (effect == underline) printf("\033[4m");
    if (effect == blink) printf("\033[5m");
    if (effect == reverse) printf("\033[7m");
    if (effect == hidden) printf("\033[8m");
    if (effect == strikethrough) printf("\033[9m");

    printf("%c", ch);
    printf("\033[0m"); // remove style
}

void Terminal::clearScreen() {
    printf("\033[2J\033[H");
}

void Terminal::refreshScreen() {
    fflush(stdout);
}
