#ifndef TERMINAL_H
#define TERMINAL_H

#include "enum.h"

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <iostream>
#include <fcntl.h>


class Terminal {
public:
    Terminal(int min_col, int min_row);
    ~Terminal();

    int getKey();
    void draw(int line, int col, char ch, int effect);
    void clearScreen();
    void refreshScreen();

private:
    struct termios orig_termios;
    int min_col, min_row;

    void enableRawMode();
    void disableRawMode();
    void checkSize();
};

#endif // TERMINAL_H
