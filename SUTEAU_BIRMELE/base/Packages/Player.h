//
// Created by florent on 26/03/25.
//
#ifndef PLAYER_H
#define PLAYER_H
#include <stdbool.h>
#include "main.h"
#include "assert.h"


typedef struct Player_s Player;

extern void Player_init(void);
extern bool Player_movement(direction_t dir);
extern Coordinates Player_get_pos(void);


#endif //PLAYER_H
