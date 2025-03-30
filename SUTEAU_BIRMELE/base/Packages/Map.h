/// @file Map.h
/// @brief Définition du module de gestion de la carte de jeu.
/// @author Florent
/// @date 26/03/25

#ifndef MAP_H
#define MAP_H

#include "main.h"

extern void Map_init(void);
extern void Map_print(void);
extern void Map_set_case(Coordinates newPos, Coordinates oldPos, char value);
extern char Map_get_case(Coordinates pos);

#endif // MAP_H