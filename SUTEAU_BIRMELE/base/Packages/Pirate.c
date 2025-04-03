//
// Created by florent on 26/03/25.
//


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Pirate.h"
#include "main.h"
#include <time.h>


struct Pirate_s{
    int position_x;
    int position_y;
};

/// @brief Représente les actions possibles pour le joueur.
typedef enum
{
    A_NOP = 0,   ///< Aucune action
    A_GO_UP,     ///< Aller vers le haut
    A_GO_DOWN,   ///< Aller vers le bas
    A_GO_LEFT,   ///< Aller vers la gauche
    A_GO_RIGHT   ///< Aller vers la droite
} action_t;


static Pirate pirate;
action_t action;     ///< Action à exécuter

//Prototype
bool Pirate_movement(direction_t dir);

extern void Pirate_init(void){
    pirate.position_x = rand()%WIDTH_MAP; // nombre entre 0 et 9
    pirate.position_y = rand()%HEIGHT_MAP; // nombre entre 0 et 9

#if USE_ASSERT
    assert(&pirate != NULL); // Vérification de l'allocation
    assert(pirate.position_x >= 0 && pirate.position_x < WIDTH_MAP);
    assert(pirate.position_y >= 0 && pirate.position_y < HEIGHT_MAP);
#endif
}
extern Coordinates Pirate_get_pos(void){
    Coordinates pos_Tresor;
    pos_Tresor.x = pirate.position_x;
    pos_Tresor.y = pirate.position_y;
    return pos_Tresor;
}

extern bool Pirate_action(Coordinates pos_player){
  if (pos_player.x == pirate.position_x && pirate.position_y > pos_player.y) {
        printf("pirate coming on your bottom \n");
        Pirate_movement(DEP_UP);
        return true;
    }
    else if (pos_player.x == pirate.position_x && pirate.position_y < pos_player.y) {
        printf("pirate coming on your top \n");
        Pirate_movement(DEP_DOWN);
        return true;
    }
    else if (pos_player.y == pirate.position_y && pirate.position_x > pos_player.x) {
        printf("pirate coming on your right\n");
        Pirate_movement(DEP_LEFT);
        return true;
    }
    else if (pos_player.y == pirate.position_y && pirate.position_x < pos_player.x) {
        printf("pirate coming on your left\n");
        Pirate_movement(DEP_RIGHT);
        return true;
    }
    return false;
}

extern bool Pirate_is_on_player(Coordinates pos_player){
    if (pos_player.x == pirate.position_x && pos_player.y == pirate.position_y ) {
      printf("pirate on player\n");
        return true;
    }
    return false;
}

extern bool Pirate_movement(direction_t dir) {
    bool moved = false;
    switch(dir) {
        case DEP_UP:
            if (!(pirate.position_y <= 0)) {
                pirate.position_y --;
                moved = true;
            }
            break;
        case DEP_DOWN:
            if (!(pirate.position_y >= HEIGHT_MAP - 1)) {
                pirate.position_y ++;
                moved = true;
            }
            break;
        case DEP_LEFT:
            if (!(pirate.position_x <= 0)) {
                pirate.position_x --;
                moved = true;
            }
            break;
        case DEP_RIGHT:
            if (!(pirate.position_x >= WIDTH_MAP - 1)) {
                pirate.position_x ++;
                moved = true;
            }
            break;
        default:
#if USE_ASSERT
            assert(0);
#else
			return false;
#endif
            break;
    }
    return moved;
 }