//
// Created by florent on 26/03/25.
//
#ifndef PLAYER_H
#define PLAYER_H
#include <stdbool.h>


typedef struct Player_s Player;

extern void Player_Init(void);
extern bool Player_Movement(direction dir);
extern coordinate Player_Get_pos(void);

#endif //PLAYER_H
