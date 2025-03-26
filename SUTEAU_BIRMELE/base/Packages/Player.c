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

extern void Player_init(void){
  player.position_x = 0;
  player.position_y = 0;
};

extern bool Player_movement(direction_t dir){
    bool moved = false;
    switch(dir){
      case DEP_UP:
        if(!(player.position_y <= 0)){
          player.position_y--;
          moved = true;
        }
        break;
      case DEP_DOWN:
        if(!(player.position_y >= HEIGHT_MAP-1)){
          player.position_y++;
          moved = true;
        }
        break;
      case DEP_LEFT:
        if(!(player.position_x <= 0)){
          player.position_x--;
          moved = true;
        }
        break;
      case DEP_RIGHT:
        if(!(player.position_x >= WIDTH_MAP-1)){
          player.position_x++;
          moved = true;
        }
        break;
      default:
        assert(0);
        break;
    }
    return moved;
}

extern Coordinates Player_get_pos(void){
  Coordinates pos;
  pos.x = player.position_x;
  pos.y = player.position_y;
  return pos;
}


