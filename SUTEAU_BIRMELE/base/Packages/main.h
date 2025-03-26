//
// Created by florent on 26/03/25.
//

#ifndef MAIN_H
#define MAIN_H


#define HEIGHT_MAP 10
#define WIDTH_MAP 10

/*typedef struct{
    int x;
    int y;
}Coordinates;

Coordinates Player;*/

typedef enum{
    DEP_UP = 0,
    DEP_DOWN,
    DEP_LEFT,
    DEP_RIGHT
}direction_t;

Coordinates Player;

void Initialisation(void);



#endif //MAIN_H
