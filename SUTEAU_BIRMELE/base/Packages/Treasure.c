//
// Created by florent on 26/03/25.
//


#include <stdlib.h>
#include "Treasure.h"
#include "main.h"
#include <time.h>

struct Treasure_s{
    int position_x;
    int position_y;
};

static Treasure treasure;

extern void Treasure_init(void){
  	treasure.position_x = rand()%10; // nombre entre 0 et 9
  	treasure.position_y = rand()%10; // nombre entre 0 et 9

    assert(&treasure != NULL); // Vérification de l'allocation
    assert(treasure.position_x >= 0 && treasure.position_x < WIDTH_MAP);
    assert(treasure.position_y >= 0 && treasure.position_y < HEIGHT_MAP);
}
extern Coordinates Treasure_get_pos(void){
    Coordinates pos_Tresor;
    pos_Tresor.x = treasure.position_x;
    pos_Tresor.y = treasure.position_y;
  return pos_Tresor;
}
