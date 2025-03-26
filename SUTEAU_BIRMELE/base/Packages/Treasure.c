//
// Created by florent on 26/03/25.
//
#include "Treasure.h"
#include "main.h"

struct Treasure_s{
    int position_x;
    int position_y;
};

static Treasure treasure;

extern void Treasure_init(void){
  treasure.position_x = 5;
  treasure.position_y = 5;
}
