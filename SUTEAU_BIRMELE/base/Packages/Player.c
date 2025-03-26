//
// Created by florent on 26/03/25.
//
#include "Player.h"
#include <stdbool.h>
struct Player_s{
    int position_x;
    int position_y;
};
static Player player;

extern void Player_Init(void){
  player.position_x = 0;
  player.position_y = 0;
};

extern bool Player_Movement(direction dir){

};

