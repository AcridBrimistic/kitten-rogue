#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
class Entity {

public:
Entity(char symbol, uint16_t row_i, uint16_t col_i, int hp_i);
  int hp;
  char ascii_char; // character
  uint16_t row, col; // position
  uint16_t gety();
  uint16_t getx();
  void move(Entity &ent, uint16_t row_m, uint16_t col_m); // moves entity 
  int gethp();
  void sethp(int hp_n);
  void attack(uint16_t row, uint16_t col, Entity &player);
};

#endif
