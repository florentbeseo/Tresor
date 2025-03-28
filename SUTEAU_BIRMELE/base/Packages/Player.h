/// @file Player.h
/// @brief Définition du module Player.
/// @author tanguy
/// @date 28/03/25

#ifndef PLAYER_V2_H
#define PLAYER_V2_H

#include <stdbool.h>
#include "main.h"
#include "assert.h"

/// @brief Structure du joueur.
typedef struct Player_s Player;

extern void Player_init(void);
extern void Player_start(void);
extern void Player_stop(void);
extern bool Player_movement(direction_t dir);
extern Coordinates Player_get_pos(void);

#endif // PLAYER_V2_H
