#include <ncurses.h>
#include "game.h"
#include "entity.h"
#include <time.h>
#include <stdlib.h>
#include "map.h"
#include "terminalscreen.h"
#include <vector>

int main() {

srand(time(NULL));

init_ncurses(stdscr);
init_pair(1, COLOR_GREEN, COLOR_BLACK);
TerminalScreen scr;

int menu_selection = 0;

while(1) {
attron(COLOR_PAIR(1));
printw("                                 Welcome to Rogueer. \n");

if(!menu_selection) attron(A_STANDOUT | A_UNDERLINE);
printw("                                   Start Game\n");
attroff(A_STANDOUT | A_UNDERLINE);
if(menu_selection) attron(A_STANDOUT | A_UNDERLINE);
printw("                                   Quit\n");
attroff(A_STANDOUT | A_UNDERLINE);
attroff(COLOR_PAIR(1));
int seed_gen;
int opt = getch();


if(opt == KEY_DOWN) ++menu_selection;
if(opt == KEY_UP) --menu_selection;
if(opt == 10) {
  if(!menu_selection) {
    printw("                          Enter Seed (0 for random)");
    scanw("-> %d", seed_gen);
    Map game_map(2*scr.get_t_height(), 2*scr.get_t_width(), 0, 0);
    Map viewport(game_map, scr.get_t_height(), scr.get_t_width(), 0, 0);
    game_map.MapDebugGen(rand() % 500, game_map);
    Entity player('@', game_map.getheight()/2, game_map.getwidth()/2, 5);    
    game(player, opt, viewport, game_map); // start game
  } else {
    break;
  }
}
if(menu_selection < 0) menu_selection = 0;
if(menu_selection > 1) menu_selection = 1;
clear();
}

endwin();
return 0;
}

void game(Entity player, int opt, Map viewport, Map game_map) {

  srand(time(NULL));


std::vector<Entity> monsters(0, Entity('D', rand() % 40, 10, 10));
attron(COLOR_PAIR(1));

game_map.move(player, 10, 10, player);
viewport.center(player);
viewport.refresh();

mvaddch(player.row, player.col, player.ascii_char);
//mvaddch(monsters[0].row, monsters[0].col, monsters[0].ascii_char);
refresh();

attroff(COLOR_PAIR(1));

time_t time = 1; // sets initial time

for(;;) {
  
  if(!(time % 2)) {
  
  if(player.row > monsters[0].row) {
    game_map.move(monsters[0], monsters[0].row + 1, monsters[0].col, player);
    ++time;
  } else if(player.row < monsters[0].row) {
    game_map.move(monsters[0], monsters[0].row - 1, monsters[0].col, player);
    ++time;
  }
  
    if(!(time % 2) && monsters[0].col < player.col) {
    game_map.move(monsters[0], monsters[0].row, monsters[0].col + 1, player);
    ++time;
  } else if(!(time % 2) && player.col < monsters[0].col) {
    game_map.move(monsters[0], monsters[0].row, monsters[0].col - 1, player);
    ++time;
  }
  mvaddch(monsters[0].row, monsters[0].col, monsters[0].ascii_char);
  refresh();  
  } else if(time % 2) {


opt = getch();
++time;
switch(opt) {
  
    case '8':
    game_map.move(player, player.row - 1, player.col, player);
    viewport.center(player);
    viewport.refresh();
    break;
    
    case '2':
    game_map.move(player, player.row + 1, player.col, player);
    viewport.center(player);
    viewport.refresh();
    break;
  
    case '4':
    game_map.move(player, player.row, player.col - 1, player);
    viewport.center(player);
    viewport.refresh();
    break;
  
    case '6':
    game_map.move(player, player.row, player.col + 1, player);
    viewport.center(player);
    viewport.refresh();
    break;
  
    case '3':
    game_map.move(player, player.row + 1, player.col + 1, player);
    viewport.center(player);
    viewport.refresh();
    break;
  
    case '9':
    game_map.move(player, player.row - 1, player.col + 1, player);
    viewport.center(player);
    viewport.refresh();
    break;
   
    case '7':
    game_map.move(player, player.row - 1, player.col - 1, player);
    viewport.center(player);
    viewport.refresh();
    break;
  
    case '1':
    game_map.move(player, player.row + 1, player.col - 1, player);
    viewport.center(player);
    viewport.refresh();
    break;
  
    default:
    break;
    }
}
refresh();
}


}

void init_ncurses(WINDOW *scr) {
  initscr();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);
  start_color();
}