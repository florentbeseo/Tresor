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
	srand( time( NULL ) );
  	treasure.position_x = rand()%10; // nombre entre 0 et 9
  	treasure.position_y = rand()%10; // nombre entre 0 et 9
}
extern Coordinates Treasure_get_pos(void){
    Coordinates pos_Tresor;
    pos_Tresor.x = treasure.position_x;
    pos_Tresor.y = treasure.position_y;
  return pos_Tresor;
}
