#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Packages/grille.h"
#include "Packages/getch.h"
#include "Packages/Map.h"
#include "Packages/Player.h"
#include "Packages/Treasure.h"
#include "Packages/main.h"

static char PLAYER_CHAR = 'j';

typedef enum
{
    INIT = 0,
    AQUISITION_CLAVIER,
    VERIF_VICTOIRE,
    VICTOIRE
}MAE_Global;

int main()
{
    char car ;
    int end = 0;
    MAE_Global GameState = INIT;
    Coordinates OldPos = {0,0};
    bool moved = false;

    while(!end){
        switch (GameState){
            case INIT:
                Initialisation();
                Player_start();
                GameState = AQUISITION_CLAVIER;
                break;
            case VERIF_VICTOIRE:
                printf("pos joueur : x : %d /y: %d\n", Player_get_pos().x, Player_get_pos().y);
                printf("pos tresor : x : %d /y: %d\n", Treasure_get_pos().x, Treasure_get_pos().y);
                if (Player_get_pos().x == Treasure_get_pos().x && Player_get_pos().y == Treasure_get_pos().y)
                {
                    printf("Vous avez trouvé le trésor !\n");
                    GameState = VICTOIRE;
                }
                else
                {
                    GameState = AQUISITION_CLAVIER;
                }
                break;
            case AQUISITION_CLAVIER:
                car = getch();
                moved = false;
                //setCase([pos_joueur_x][pos_joueur_y] = ' ';
                switch(car)
                {
                    case 'q':
                        end = 1;
                    break;
                    case 'i':
                        moved = Player_movement(DEP_UP);
                    break;
                    case 'k':
                        moved = Player_movement(DEP_DOWN);
                    break;
                    case 'j':
                        moved = Player_movement(DEP_LEFT);
                    break;
                    case 'l':
                        moved = Player_movement(DEP_RIGHT);
                    break;
                }
                if (moved){
                      Map_set_case(Player_get_pos(), OldPos, PLAYER_CHAR);
                      Map_print();
                      OldPos = Player_get_pos();
                      GameState = VERIF_VICTOIRE;
                }
                break;
            case VICTOIRE:
                printf("Vous avez gagné !\n");
                end = 1;
                break;
            default:
                break;
        }
    }
    printf("Fin du jeu\n");
    return 0;
}

void Initialisation(void)
{
    Map_init();
    Player_init();
    Treasure_init();

    Map_set_case(Player_get_pos(),Player_get_pos(), PLAYER_CHAR);
    Map_set_case(Treasure_get_pos(),Treasure_get_pos(), 'T');

    Map_print();
}




