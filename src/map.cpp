#include "perlin.h"
#include "map.h"
#include "entity.h"
#include <ncurses.h>
#include "perlin.h"

void Map::MapDebugGen(const unsigned int &seed, Map &game_map) {

PerlinNoise pn(seed);

for(int i = 0; i < game_map.getheight(); i++) {
    for(int j = 0; j < game_map.getwidth(); j++) {
        double x = (double)j/((double)game_map.getwidth());
        double y = (double)i/((double)game_map.getheight());

        double n = pn.noise(10 * x , 10 * y, 0.8);

        init_pair(2, COLOR_BLUE, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        if(n < 0.26) { // water/lava
            attron(COLOR_PAIR(2));
            mvwaddch(game_map.win(), i, j, '~');
        } else if(n >= 0.26 && n < 0.30) {
            mvwaddch(game_map.win(), i, j, '%');
        } else if(n >= 0.26 && n < 0.55) { // floor
            mvwaddch(game_map.win(), i, j, '.');
        } else if(n >= 0.55 && n < 0.64) { // visible wall
            attron(COLOR_PAIR(3));
            mvwaddch(game_map.win(), i, j, '#');
        } else {
            mvwaddch(game_map.win(), i, j, ' '); // unknown
        }
    }
}

}

Map::Map(int row_amount, int col_amount, int row_k, int col_k) {

row_k = row_k;
col_k = col_k;
height = row_amount;
width = col_amount;
child = false;
parent = NULL;
mw = newwin(row_amount, col_amount, row_k, col_k);

}

Map::Map(Map &sw, int row_amount, int col_amount, int row_k, int col_k) {
    

    row_k = row_k;
    col_k = col_k;
    height = row_amount;
    width = col_amount;
    child = true;
    parent = sw.win();
    mw = derwin(sw.win(), row_amount, col_amount, row_k, col_k);
    
}

uint8_t Map::getheight() {
    return height;
}
uint8_t Map::getwidth() {
    return width;
}
WINDOW* Map::win() {
    return mw;
}
void Map::move(Entity &ent, uint16_t row_m, uint16_t col_m, Entity &player) {
char moveto = mvwinch(mw, row_m, col_m);
if(moveto != '.') {
  if(moveto == '#' || moveto == '~' || moveto == ' ') {
      if(moveto == '@') ent.attack(row_m, col_m, player);
      return;
  } else {
      ent.attack(row_m, col_m, player);
  }
}
mvwaddch(mw, ent.row, ent.col, '.');
ent.row = row_m;
ent.col = col_m;
mvwaddch(mw, ent.row, ent.col, ent.ascii_char);
refresh();
}

void Map::center(Entity &x) {
	if(child) {
        int rr = row_k; 
        int cc = col_k, hh, ww;
		int _r = x.gety() - height/2;
		int _c = x.getx() - width/2;

		getmaxyx(parent, hh, ww);

		if(_c + width >= ww) {
			int delta = ww - (_c + width);
			cc = _c + delta;
		}
		else {
			cc = _c;
		}

		if(_r +height >= hh) {
			int delta = hh - (_r + height);
			rr = _r + delta;
		}
		else {
			rr = _r;
		}

		if (_r < 0) {
			rr = 0;
		}

		if (_c < 0) {
			cc = 0;
		}


		movewin(rr, cc);
	}
}

void Map::movewin(int r, int c) {
	if(child) {
		mvderwin(mw, r, c);
		row_k = r;
		col_k = c;
		refresh();
	}
}

void Map::refresh() {
	if(child) {
		touchwin(parent);
	}
	wrefresh(mw);
}