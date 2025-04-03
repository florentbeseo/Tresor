/// @file Player.c
/// @brief Implémentation du module Player
/// @author tanguy
/// @date 28/03/25

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "Player.h"

/// @brief Représente les états possibles du joueur.
typedef enum
{
    S_AUCISSE = 0, ///< État Init
    S_REPOS,       ///< Joueur au repos
    S_ACTIF,       ///< Joueur en mouvement
    S_DEAD,        ///< Joueur mort
    NB_STATE       ///< Nombre total d'états
} state_t;

/// @brief Représente les événements pouvant affecter le joueur.
typedef enum
{
    E_UP = 0, ///< Déplacement vers le haut
    E_DOWN,   ///< Déplacement vers le bas
    E_LEFT,   ///< Déplacement vers la gauche
    E_RIGHT,  ///< Déplacement vers la droite
    E_STOP,   ///< Arrêt du joueur
    NB_EVENT  ///< Nombre total d'événements
} event_t;

/// @brief Représente les actions possibles pour le joueur.
typedef enum
{
    A_NOP = 0,   ///< Aucune action
    A_GO_UP,     ///< Aller vers le haut
    A_GO_DOWN,   ///< Aller vers le bas
    A_GO_LEFT,   ///< Aller vers la gauche
    A_GO_RIGHT   ///< Aller vers la droite
} action_t;

/// @brief Structure d'une transition d'état.
typedef struct
{
    state_t destination; ///< État de destination
    action_t action;     ///< Action à exécuter
} transition_t;

/// @brief Structure du joueur.
struct Player_s {
    int position_x; ///< Position X du joueur
    int position_y; ///< Position Y du joueur
    state_t state;  ///< État actuel du joueur
    int HP;
};

/// @brief Prototypage de la fonction interne.
/// @param event L'événement à traiter
static void run(event_t event);

/// @brief Instance du joueur.
static Player player;

/// @brief Table de transition des états.
static const transition_t transition_table[NB_STATE][NB_EVENT] =
{
    [S_REPOS][E_UP] = {S_REPOS, A_GO_UP},
    [S_REPOS][E_DOWN] = {S_REPOS, A_GO_DOWN},
    [S_REPOS][E_LEFT] = {S_REPOS, A_GO_LEFT},
    [S_REPOS][E_RIGHT] = {S_REPOS, A_GO_RIGHT},
    [S_REPOS][E_STOP] = {S_DEAD, A_NOP}
};

/// @brief Initialise le joueur.
/// @details Cette fonction met le joueur dans un état initial avec des valeurs par défaut.
extern void Player_init(void) {
    player.position_x = 0;
    player.position_y = 0;
    player.HP = HP_DEFAULT;
    player.state = S_DEAD;
}

/// @brief Definit le nombre de HP du joueur
extern void Player_setHP(int HP){
  player.HP = HP;
}

/// @brief Retourne les nonbre de HP du joueur
/// @return Un entier correspondant au HP du joueur.
extern int Player_getHP(void){
  return player.HP;
}

/// @brief Reduit la vie du joueur de 1 HP.
/// @details Cette fonction enlève un PV au joueur a chaque appel, si le joueur se retrouve à 0HP la fonction renvoi true.
extern bool Player_hit(void){
#if USE_ASSERT
	assert(player.HP > 0);
#endif
    player.HP--;
    if (player.HP == 0) {
      return true;
    }
    return false;
}

/// @brief Retourne la position actuelle du joueur.
/// @return La structure contenant les coordonnées du joueur.
extern Coordinates Player_get_pos(void) {
    Coordinates pos;
    pos.x = player.position_x;
    pos.y = player.position_y;
    return pos;
}

/// @brief Démarre le joueur en le mettant à l'état REPOS.
extern void Player_start(void) {
#if USE_ASSERT
    assert(player.state == S_DEAD);
    assert(player.position_x == 0 && player.position_y == 0);
    assert(player.HP == HP_DEFAULT);
#endif
    player.state = S_REPOS;
}

/// @brief Arrête le joueur et la MaE.
extern void Player_stop(void) {
    run(E_STOP);
}

/// @brief Gère le déplacement du joueur.
/// @param dir Direction du déplacement.
/// @return true si le déplacement a été effectué, sinon false.
extern bool Player_movement(direction_t dir) {
#if USE_ASSERT
    assert(player.state != S_DEAD);
  	assert(player.state == S_REPOS);
#endif
    switch(dir) {
        case DEP_UP:
            if (!(player.position_y <= 0)) {
                run(E_UP);
                return true;
            }
            break;
        case DEP_DOWN:
            if (!(player.position_y >= HEIGHT_MAP - 1)) {
                run(E_DOWN);
                return true;
            }
            break;
        case DEP_LEFT:
            if (!(player.position_x <= 0)) {
                run(E_LEFT);
                return true;
            }
            break;
        case DEP_RIGHT:
            if (!(player.position_x >= WIDTH_MAP - 1)) {
                run(E_RIGHT);
                return true;
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
    return false;
}

/// @brief Exécute une transition d'état en fonction de l'événement reçu.
/// @param event L'événement à traiter.
static void run(event_t event) {
#if USE_ASSERT
    assert(player.state != S_DEAD);
#endif
    state_t destination = transition_table[player.state][event].destination;
    action_t todo_action = transition_table[player.state][event].action;
    switch(todo_action) {
        case A_NOP:
            break;
        case A_GO_UP:
            player.position_y--;
            break;
        case A_GO_DOWN:
            player.position_y++;
            break;
        case A_GO_LEFT:
            player.position_x--;
            break;
        case A_GO_RIGHT:
            player.position_x++;
            break;
        default:
#if USE_ASSERT
            assert(0);
#else
			return false;
#endif
            break;
    }
    if (destination != S_AUCISSE) {
        player.state = destination;
    }
}
