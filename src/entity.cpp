#include "entity.h"
#include "map.h"
#include <curses.h>

#include <stdint.h>

Entity::Entity(char symbol, uint16_t row_i, uint16_t col_i, int hp_i):
  ascii_char(symbol),
  row(row_i),
  col(col_i),
  hp(hp_i)
{
}

int Entity::gethp() {
return hp;
}
void Entity::sethp(int hp_n) {
hp = hp_n;
}

uint16_t Entity::gety() {
  return row;
}
uint16_t Entity::getx() {
  return col;
}


void Entity::attack(uint16_t row, uint16_t col, Entity &player) {

  if(row == player.gety() && col == player.getx()) {
    player.sethp(player.gethp() - 4);
  }


}

