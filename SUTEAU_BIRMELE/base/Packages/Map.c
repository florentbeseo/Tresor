//
// Created by florent on 26/03/25.
//
#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "grille.h"

static char **game_map;
extern void Map_init(void){


    game_map = (char **)malloc(HEIGHT_MAP * sizeof(char *));
      for (int i = 0; i < HEIGHT_MAP; i++) {
          game_map[i] = (char *)malloc(WIDTH_MAP * sizeof(char));
      }
    //Remplissage du tableau
    for(int i=0; i< HEIGHT_MAP; i++)
    {
        for(int j=0; j<WIDTH_MAP; j++)
        {
            game_map[i][j] = ' ';
        }
    }
}

extern void Map_print(void){
    system("clear");
    grille_print(game_map, WIDTH_MAP, HEIGHT_MAP);
}
extern void Map_set_case(Coordinates newPos, Coordinates oldPos, char value){
    game_map[oldPos.y][oldPos.x] = ' ';
    game_map[newPos.y][newPos.x] = value;
}

/*
//Liberation de la memoire pour le tableau
    for (int i = 0; i < HEIGHT_MAP; i++) {
        free(game_map[i]);
    }
    free(game_map);

}*/

