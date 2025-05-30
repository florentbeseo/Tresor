/// @file Pirate.h
/// @brief Définition du module de gestion du pirate.
/// @author Florent
/// @date 26/03/25
#ifndef PIRATE_H
#define PIRATE_H
#include <stdbool.h>
#include "main.h"
#include "assert.h"

typedef struct Pirate_s Pirate;



extern void Pirate_init(void);
extern Coordinates Pirate_get_pos(void);
extern bool Pirate_action(Coordinates pos_player);
extern bool Pirate_is_on_player(Coordinates pos_player);

#endif //PIRATE_H
