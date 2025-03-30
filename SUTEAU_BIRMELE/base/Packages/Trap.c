//
// Created by florent on 26/03/25.
//


#include <stdlib.h>
#include "Trap.h"
#include "main.h"
#include <time.h>


extern Coordinates Trap_get_pos(Trap *trap){
	Coordinates pos_Trap;
	pos_Trap.x = trap->position_x;
	pos_Trap.y = trap->position_y;
	return pos_Trap;
}
extern int Trap_get_number(Trap *trap){
	int numTrap = trap->numTrap;
	return numTrap;
}


static int nbInstances = 0;
extern Trap *Trap_new() {
	Trap *this = (Trap*)calloc(1,sizeof(Trap)); // Allocation mémoire
	this->numTrap = nbInstances;
    this->position_x = rand()%WIDTH_MAP; // nombre entre 0 et 9
    this->position_y = rand()%HEIGHT_MAP; // nombre entre 0 et 9
	assert(this != NULL); // Vérification de l'allocation
    assert(this->position_x >= 0 && this->position_x < WIDTH_MAP);
    assert(this->position_y >= 0 && this->position_y < HEIGHT_MAP);
    nbInstances++;
	return this;
}

extern void Trap_delete(Trap *this) {
	free ((Trap *)this);
}
