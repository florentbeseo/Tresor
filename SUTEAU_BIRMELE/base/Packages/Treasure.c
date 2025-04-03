/// @file Treasure.c
/// @brief Implémentation de la gestion du trésor dans le jeu.
/// @author Florent
/// @date 26/03/25


#include <stdlib.h>
#include "Treasure.h"
#include "main.h"
#include <time.h>
/// @struct Treasure_s
/// @brief Structure représentant un trésor avec ses coordonnées.
struct Treasure_s{
    int position_x;///< Position X du trésor sur la carte.
    int position_y;///< Position Y du trésor sur la carte.
};

static Treasure treasure;


/// @brief Initialise la position du trésor de manière aléatoire.
///
/// La position est générée aléatoirement entre 0 et WIDTH_MAP - 1 pour X
/// et entre 0 et HEIGHT_MAP - 1 pour Y.
/// Des vérifications sont effectuées pour s'assurer que les coordonnées sont valides.
extern void Treasure_init(void){
#if USE_ASSERT
    assert(&treasure != NULL); // Vérification de l'allocation
#endif

  	treasure.position_x = rand()%10; // nombre entre 0 et 9
  	treasure.position_y = rand()%10; // nombre entre 0 et 9

#if USE_ASSERT
    assert(treasure.position_x >= 0 && treasure.position_x < WIDTH_MAP);
    assert(treasure.position_y >= 0 && treasure.position_y < HEIGHT_MAP);
#endif
}

/// @brief Récupère la position actuelle du trésor.
///
/// @return Les coordonnées du trésor sous forme d'une structure Coordinates.
extern Coordinates Treasure_get_pos(void){
    Coordinates pos_Tresor;
    pos_Tresor.x = treasure.position_x;
    pos_Tresor.y = treasure.position_y;
  return pos_Tresor;
}
