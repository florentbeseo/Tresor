/// @file Map.c
/// @brief Implémentation du module de gestion de la carte de jeu.
/// @author Florent
/// @date 26/03/25

#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "grille.h"

/// @brief Pointeur vers la carte du jeu.
static char **game_map;

/// @brief Initialise la carte du jeu.
/// @details Alloue dynamiquement une grille de jeu et initialise toutes les cases à ' '.
extern void Map_init(void) {
    game_map = (char **)malloc(HEIGHT_MAP * sizeof(char *));
    for (int i = 0; i < HEIGHT_MAP; i++) {
        game_map[i] = (char *)malloc(WIDTH_MAP * sizeof(char));
    }

    // Remplissage de la carte avec des espaces
    for (int i = 0; i < HEIGHT_MAP; i++) {
        for (int j = 0; j < WIDTH_MAP; j++) {
            game_map[i][j] = ' ';
        }
    }
}

/// @brief Affiche la carte du jeu.
/// @details Utilise la fonction `grille_print` pour afficher la grille sur la console.
extern void Map_print(void) {
//    system("clear"); // Effacement de l'écran (commenté pour éviter des problèmes de compatibilité)
    grille_print(game_map, WIDTH_MAP, HEIGHT_MAP);
}

/// @brief Modifie une case de la carte.
/// @param newPos Coordonnées de la nouvelle position.
/// @param oldPos Coordonnées de l'ancienne position.
/// @param value Caractère à placer à la nouvelle position.
/// @details La case de l'ancienne position est vidée (' ') et la nouvelle position est mise à jour.
extern void Map_set_case(Coordinates newPos, Coordinates oldPos, char value) {
    game_map[oldPos.y][oldPos.x] = ' ';
    game_map[newPos.y][newPos.x] = value;
}

extern char Map_get_case(Coordinates pos) {
    return game_map[pos.y][pos.x];
}
/*
/// @brief Libère la mémoire allouée pour la carte.
/// @details Parcourt la carte et libère chaque ligne, puis le tableau principal.
void Map_free(void) {
    for (int i = 0; i < HEIGHT_MAP; i++) {
        free(game_map[i]);
    }
    free(game_map);
}
*/
