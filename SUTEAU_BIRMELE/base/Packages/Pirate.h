
//
// Created by florent on 26/03/25.
//

#ifndef PIRATE_H
#define PIRATE_H
#include <stdbool.h>
#include "main.h"
#include "assert.h"

typedef struct Pirate_s Pirate;



extern void Pirate_init(void);
extern Coordinates Pirate_get_pos(void);
extern Pirate_state_t Pirate_see_player(Coordinates pos_player);
extern bool Pirate_is_on_player(Coordinates pos_player);
extern bool Pirate_movement(direction_t dir);
//extern coordinate Pirate get_pos();

#endif //PIRATE_H
