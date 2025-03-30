//
// Created by florent on 26/03/25.
//
#include "Trap.h"
#ifndef MAIN_H
#define MAIN_H

#define AFFICHER_DEBUG 1

#if AFFICHER_DEBUG
    #define AFFICHER_TRESOR
    #define AFFICHER_PIEGES
#endif

#define HEIGHT_MAP 10
#define WIDTH_MAP 10
#define HP_DEFAULT 3

typedef struct{
    int x;
    int y;
}Coordinates;

typedef enum{
    DEP_UP = 0,
    DEP_DOWN,
    DEP_LEFT,
    DEP_RIGHT
}direction_t;

void Initialisation(void);



#endif //MAIN_H
