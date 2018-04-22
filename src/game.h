#ifndef GAME_H
#define GAME_H

#include "entity.h"
#include "map.h"

void init_ncurses(WINDOW* scr);
void game(Entity player, int opt, Map viewport, Map game_map);

#endif
