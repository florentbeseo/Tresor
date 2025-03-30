/**
* @file main.c
 * @brief Module principal du jeu.
 *
 * Ce fichier contient l'initialisation du jeu et la gestion de la boucle principale.
 * Il interagit avec les modules Player, Map, et Treasure pour gérer l'état du jeu.
 *
 * @section description Description du jeu
 * Le jeu consiste à déplacer un joueur sur une carte. La carte est représentée par une grille
 * et le joueur peut se déplacer dans différentes directions.
 *
 * @section modules Modules du projet
 * - Player : Gère l'état et les actions du joueur.
 * - Map : Gère la carte du jeu, y compris l'affichage et les modifications des cases.
 * - Treasure : Gère le trésor et ses interactions avec le joueur.
 */

/**
 * @mainpage
 * @brief Module principal du jeu.
 *
 * @dotfile diagrameClass.puml
 */



#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Packages/grille.h"
#include "Packages/getch.h"
#include "Packages/Map.h"
#include "Packages/Player.h"
#include "Packages/Treasure.h"
#include "Packages/Trap.h"
#include "Packages/main.h"
#include <assert.h>


#define NB_TRAP_DEFAULT 5
#define NB_TRAP_MAX 20

Trap *trap_tab[NB_TRAP_MAX];

static char PLAYER_CHAR = 'j';
static char TRAP_CHAR = 'X';
static char TREASURE_CHAR = 'O';

typedef enum
{
    INIT = 0,
    AQUISITION_CLAVIER,
    VERIF_VICTOIRE,
    VICTOIRE
}MAE_Global;

void reforme_trap_tab(int nb_trap_sup);

static int nb_trap = 0;

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
                for (int testTrap = 0; testTrap < nb_trap; testTrap++){
                  printf("Trap num %d\n", testTrap);
                  assert(trap_tab[testTrap] != NULL);
                }
                Player_start();
                GameState = AQUISITION_CLAVIER;
                break;
            case VERIF_VICTOIRE:
#ifdef AFFICHER_TRESOR
              	printf("pos joueur : x : %d /y: %d\n", Player_get_pos().x, Player_get_pos().y);
                printf("pos tresor : x : %d /y: %d\n", Treasure_get_pos().x, Treasure_get_pos().y);
#endif
#ifdef AFFICHER_PIEGES
                for (int i = 0; i < nb_trap; i++)
                {
                    if (trap_tab[i] != NULL)
                      	printf("tab [%d] / piege num %d : x : %d /y: %d\n", i, Trap_get_number(trap_tab[i]), Trap_get_pos(trap_tab[i]).x, Trap_get_pos(trap_tab[i]).y);
                }
#endif
                if (Player_get_pos().x == Treasure_get_pos().x && Player_get_pos().y == Treasure_get_pos().y)
                {
                    printf("Vous avez trouvé le trésor !\n");
                    GameState = VICTOIRE;
                }
                else
                {
                    for (int i = 0; i < nb_trap; i++)
                    {
                        if (Player_get_pos().x == Trap_get_pos(trap_tab[i]).x && Player_get_pos().y == Trap_get_pos(trap_tab[i]).y)
                        {

                            reforme_trap_tab(i);
                            Trap_delete(trap_tab[nb_trap-1]);
                            nb_trap--;
                            printf("Vous êtes tombé dans un piège !\n");

                        }
                    }
                    GameState = AQUISITION_CLAVIER;
                }
                break;
            case AQUISITION_CLAVIER:
                car = getch();
                moved = false;
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
                      OldPos = Player_get_pos();
                      Map_print();
                      printf("pieges : %d\n", nb_trap);
                      GameState = VERIF_VICTOIRE;
                }
                break;
            case VICTOIRE:
                Player_stop();
                printf("Vous avez gagné !\n");
                end = 1;
                for (int k = 0; k<nb_trap; k++)
                {
                    Trap_delete(Trap_new());
                }
                break;
            default:
                break;
        }
    }
    printf("Fin du jeu\n");
    return 0;
}

void reforme_trap_tab(int idx_nb_trap_sup)
{
  	Trap *temp = trap_tab[idx_nb_trap_sup];
    printf("reforme tab : \nnb_trap : %d\n", nb_trap);
    for (int i = idx_nb_trap_sup; i < nb_trap-1; i++)
    {
        printf("tab[%d] = tab[%d]\n", i, i+1);
        trap_tab[i] = trap_tab[i + 1];
    }
    trap_tab[nb_trap-1] = temp;
}
void Initialisation(void)
{
    bool Treasure_OK = false;
    bool Trap_OK = false;
    nb_trap = NB_TRAP_DEFAULT;
    Map_init();
    Player_init();
    while(!Treasure_OK)
    {
        Treasure_init();
        if (Player_get_pos().x != Treasure_get_pos().x || Player_get_pos().y != Treasure_get_pos().y)
        {
            Treasure_OK = true;
        }
    }

    for (int i = 0; i < nb_trap; i++)
    {
        Trap_OK = false;
        while(!Trap_OK)
        {
			trap_tab[i] = Trap_new();
            if (Player_get_pos().x != Trap_get_pos(trap_tab[i]).x || Player_get_pos().y != Trap_get_pos(trap_tab[i]).y)
            {
                Trap_OK = true;
            }
            for (int j = 0; j < i; j++)
            {
                if (Trap_get_pos(trap_tab[i]).x == Trap_get_pos(trap_tab[j]).x && Trap_get_pos(trap_tab[i]).y == Trap_get_pos(trap_tab[j]).y)
                {
                    Trap_OK = false;
                }
            }
        }
#ifdef AFFICHER_PIEGES
        Map_set_case(Trap_get_pos(trap_tab[i]), Trap_get_pos(trap_tab[i]), TRAP_CHAR);
#endif
    }

    Map_set_case(Player_get_pos(),Player_get_pos(), PLAYER_CHAR);
    assert(Map_get_case(Player_get_pos()) == PLAYER_CHAR);

#ifdef AFFICHER_TRESOR
    Map_set_case(Treasure_get_pos(),Treasure_get_pos(), TREASURE_CHAR);
#endif
    Map_print();
}




