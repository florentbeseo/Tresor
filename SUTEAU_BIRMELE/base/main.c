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

/// @brief Tableau des pièges.
Trap *trap_tab[NB_TRAP_MAX];

/// @brief Caractère représentant le joueur.
static char PLAYER_CHAR = 'j';
/// @brief Caractère représentant un piège.
static char TRAP_CHAR = 'X';
/// @brief Caractère représentant le trésor.
static char TREASURE_CHAR = 'O';

/// @brief États possibles de la machine à états globale.
typedef enum
{
    INIT = 0, ///< État d'initialisation.
    AQUISITION_CLAVIER, ///< État d'acquisition clavier.
    VERIF_VICTOIRE, ///< État de vérification de la victoire.
    VICTOIRE, ///< État de victoire.
    LOOSE ///< Etat de défaite du joueur.
} MAE_Global;

/// @brief Réforme le tableau des pièges.
/// @param nb_trap_sup Nombre de pièges à supprimer.
void reforme_trap_tab(int nb_trap_sup);

/// @brief Nombre de pièges.
static int nb_trap_start = 0;
static int nb_trap = 0;

/**
 * @brief Fonction principale du jeu. Suit les Etats de MAE_Global.
 * @return Code de retour du programme.
 */
int main()
{
    bool trap_OK = false;
    char car;
    int end = 0;
    int tmpDead = 0;
    MAE_Global GameState = INIT;
    Coordinates OldPos = {0, 0};
    bool moved = false;
    nb_trap_start = NB_TRAP_DEFAULT;


    while (!end) {
        switch (GameState) {
            case INIT:
              	printf("Bonjour et bienvenue dans le jeu !\n");
                printf("Vous devez trouver le trésor sans tomber dans les pièges !\n");

                while (!trap_OK) {
                    printf("Combien de pièges voulez vous ? (max %d)\n", NB_TRAP_MAX);
                    if (scanf("%d",&nb_trap_start)==1){
                        if (nb_trap_start > 0 && nb_trap_start <= NB_TRAP_MAX) {
                            trap_OK = true;
                        } else {
                            printf("Nombre de pièges invalide. Veuillez réessayer.\n");
                        }
                    }else{
                        printf("Entrée invalide. Veuillez entrer un nombre.\n");
                        char c;
                        while ((c = getchar()) != '\n' && c != EOF);//EndOfFile , Tant que c est pas EOF ou \n on vide le buffer d'entrée
                        }
                }
				trap_OK = false;
                printf("nb_trap : %d\n", nb_trap_start);
                nb_trap = nb_trap_start;
                Initialisation();
                for (int testTrap = 0; testTrap < nb_trap_start; testTrap++) {
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
                for (int i = 0; i < nb_trap; i++) {
                    if (trap_tab[i] != NULL)
                        printf("tab [%d] / piege num %d : x : %d /y: %d\n", i, Trap_get_number(trap_tab[i]), Trap_get_pos(trap_tab[i]).x, Trap_get_pos(trap_tab[i]).y);
                }
#endif
                if (Player_get_pos().x == Treasure_get_pos().x && Player_get_pos().y == Treasure_get_pos().y) {
                    printf("Vous avez trouvé le trésor !\n");
                    GameState = VICTOIRE;
                } else {
                    for (int i = 0; i < nb_trap; i++) {
                        if (Player_get_pos().x == Trap_get_pos(trap_tab[i]).x && Player_get_pos().y == Trap_get_pos(trap_tab[i]).y) {
                            reforme_trap_tab(i);
                            Trap_delete(trap_tab[nb_trap - 1]);
                            nb_trap--;
                            printf("Vous êtes tombé dans un piège !\n");
                            if(Player_hit()){//Si retour de la fonction négatif le joueur est mort !
                                  tmpDead=1;
                            }

                        }
                    }
                    if(tmpDead==1){
                      GameState = LOOSE;
                      tmpDead=0;
                    }else{
                    	GameState = AQUISITION_CLAVIER;
                    }

                }
                break;
            case AQUISITION_CLAVIER:
                car = getch();
                moved = false;
                switch (car) {
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
                if (moved) {
                    Map_set_case(Player_get_pos(), OldPos, PLAYER_CHAR);
                    OldPos = Player_get_pos();
                    Map_print();
                    printf("pieges : %d\n", nb_trap);
                    printf("Joueur HP : %d\n", Player_getHP());
                    GameState = VERIF_VICTOIRE;
                }
                break;
            case VICTOIRE:
                Player_stop();
                printf("Vous avez gagné !\n");
                GameState = INIT;
                for (int k = 0; k < nb_trap; k++) {
                    Trap_delete(Trap_new());
                }
                break;
            case LOOSE:
              Player_stop();
              printf("Vous êtes mort, vous avez perdu !\n");
              GameState = INIT;
              for (int k = 0; k < nb_trap; k++) {
                  Trap_delete(Trap_new());
              }
              break;
            default:
                break;
        }
    }
    printf("stop du jeu\n");
    return 0;
}

/**
 * @brief Reforme le tableau des pièges, en placant le piège à supprimer à la fin.
 * @param idx_nb_trap_sup Index du piège à supprimer.
 */
void reforme_trap_tab(int idx_nb_trap_sup)
{
    Trap *temp = trap_tab[idx_nb_trap_sup];
    printf("reforme tab : \nnb_trap : %d\n", nb_trap);
    for (int i = idx_nb_trap_sup; i < nb_trap - 1; i++) {
        printf("tab[%d] = tab[%d]\n", i, i + 1);
        trap_tab[i] = trap_tab[i + 1];
    }
    trap_tab[nb_trap - 1] = temp;
}

/**
 * @brief Initialise le jeu en appellant les initialisations des modules (Map, Player, Treasure, Trap).
 */
void Initialisation(void)
{
    bool Treasure_OK = false;
    bool Trap_OK = false;
    Map_init();
    Player_init();
    while (!Treasure_OK){
        Treasure_init();
        if (Player_get_pos().x != Treasure_get_pos().x || Player_get_pos().y != Treasure_get_pos().y) {
            Treasure_OK = true;
        }
    }

    for (int i = 0; i < nb_trap_start; i++) {
        Trap_OK = false;
        while (!Trap_OK) {
            trap_tab[i] = Trap_new();
            if (Player_get_pos().x != Trap_get_pos(trap_tab[i]).x || Player_get_pos().y != Trap_get_pos(trap_tab[i]).y) {
                Trap_OK = true;
            }
            for (int j = 0; j < i; j++) {
                if (Trap_get_pos(trap_tab[i]).x == Trap_get_pos(trap_tab[j]).x && Trap_get_pos(trap_tab[i]).y == Trap_get_pos(trap_tab[j]).y) {
                    Trap_OK = false;
                }
            }
        }
#ifdef AFFICHER_PIEGES
        Map_set_case(Trap_get_pos(trap_tab[i]), Trap_get_pos(trap_tab[i]), TRAP_CHAR);
#endif
    }

    Map_set_case(Player_get_pos(), Player_get_pos(), PLAYER_CHAR);
    assert(Map_get_case(Player_get_pos()) == PLAYER_CHAR);

#ifdef AFFICHER_TRESOR
    Map_set_case(Treasure_get_pos(), Treasure_get_pos(), TREASURE_CHAR);
#endif
    Map_print();
}