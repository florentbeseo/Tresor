
//
// Created by florent on 28/03/25.
//

#ifndef TRAP_H
#define TRAP_H
#include "main.h"
#include "assert.h"

struct Trap_s{
    int position_x;
    int position_y;
    int numTrap;
};
typedef struct Trap_s Trap;


extern Coordinates Trap_get_pos(Trap *trap);
extern int Trap_get_number(Trap *trap);

extern Trap *Trap_new();
extern void Trap_delete(Trap *this);

//extern coordinate Trap get_pos();

#endif //TRAP_H
