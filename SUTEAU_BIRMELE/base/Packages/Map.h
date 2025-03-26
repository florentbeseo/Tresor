//
// Created by florent on 26/03/25.
//

#ifndef MAP_H
#define MAP_H
#include "main.h"

extern void Map_init(void);
extern void Map_print(void);
extern void Map_set_case(Coordinates newPos, Coordinates oldPos, char value);

#endif //MAP_H
