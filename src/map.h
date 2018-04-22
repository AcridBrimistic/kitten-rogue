#ifndef MAP_H
#define MAP_H

#include <ncurses.h>
#include "entity.h"

class Map {


WINDOW *mw;
WINDOW *parent;
bool child;
int row_k, col_k;

public:
    uint8_t height, width;
    Map(int row_amount, int col_amount, int row_w, int col_w);
Map(Map &sw, int row_amount, int col_amount, int row_w, int col_w);
void center(Entity &x);
void movewin(int r, int c);
void refresh();
uint8_t getheight();
uint8_t getwidth();
WINDOW* win();
void move(Entity &ent, uint16_t row_m, uint16_t col_m, Entity &player);
void MapDebugGen(const unsigned int &seed, Map &gamemap);
};
#endif