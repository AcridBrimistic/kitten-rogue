#ifndef TERMINALSCREEN_H
#define TERMINALSCREEN_H

#include <ncurses.h>

class TerminalScreen {

int t_height, t_width;
public:
    int get_t_height();
    int get_t_width();
    TerminalScreen();

};


#endif