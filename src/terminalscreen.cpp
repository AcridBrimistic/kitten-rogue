#include "terminalscreen.h"

TerminalScreen::TerminalScreen() {

    getmaxyx(stdscr, t_height, t_width);


}

int TerminalScreen::get_t_height() {
    return t_height;
}

int TerminalScreen::get_t_width() {
    return t_width;
}