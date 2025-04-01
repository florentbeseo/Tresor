//
// Created by florent on 26/03/25.
//
#include "Trap.h"
#ifndef MAIN_H
#define MAIN_H

#define AFFICHER_DEBUG 1

#if AFFICHER_DEBUG
    #define AFFICHER_TRESOR
    #define AFFICHER_PIRATE
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

typedef enum{
    S_BLIND = 0,
    S_SEE_FROM_LEFT,
    S_SEE_FROM_RIGHT,
    S_SEE_FROM_UP,
    S_SEE_FROM_DOWN,
}Pirate_state_t;

void Initialisation(void);



#endif //MAIN_H
