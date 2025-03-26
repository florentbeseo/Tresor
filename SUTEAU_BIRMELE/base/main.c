#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Packages/grille.h"
#include "Packages/getch.h"
#include "Packages/Map.h"
#include "Packages/Player.h"
#include "Packages/main.h"


typedef enum
{
    INIT = 0,
    AQUISITION_CLAVIER,
    VERIF_VICTOIRE,
    VICTOIRE
}MAE_Global;

typedef enum
{
    D_Droite = 0,
    D_Gauche,
    D_Haut,
    D_Bas
}MAE_Deplacement;

int main()
{
    char car ;
    int end = 0;
    char **test_grille;
    int pos_joueur_x = 0;
    int pos_joueur_y = 0;
    MAE_Global GameState = INIT;
    MAE_Deplacement deplacementState;
    char PLAYER_CHAR = 'j';
    Coordinates OldPos = {0,0};

    while(!end){
        switch (GameState){
            case INIT:
                Initialisation();
                GameState = AQUISITION_CLAVIER;
                break;
            case VERIF_VICTOIRE:
            GameState = AQUISITION_CLAVIER;
            break;
            case AQUISITION_CLAVIER:
                car = getch();
                //setCase([pos_joueur_x][pos_joueur_y] = ' ';
                switch(car)
                {
                    case 'q':
                        end = 1;
                    break;
                    case 'i':
                        Player_movement(DEP_UP);
                    break;
                    case 'k':
                        Player_movement(DEP_DOWN);
                    break;
                    case 'j':
                        Player_movement(DEP_LEFT);
                    break;
                    case 'l':
                        Player_movement(DEP_RIGHT);
                    break;
                }
                if (!end){
                      Map_set_case(Player_get_pos(), OldPos, PLAYER_CHAR);
                      Map_print();
                      OldPos = Player_get_pos();
                      GameState = VERIF_VICTOIRE;
                }
                break;
            case VICTOIRE:
                end = 1;
                break;
            default:
                break;
        }
    }
    printf("finnnn\n");
    return 0;
}

void Initialisation(void)
{
    Player_init();

    Map_init();
    Map_set_case(Player_get_pos(),Player_get_pos(), 'j');
    Map_print();
}




