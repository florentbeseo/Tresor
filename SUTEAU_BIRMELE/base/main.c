#include <stdlib.h>
#include <stdio.h>
#include "grille.h"
#include "getch.h"
#include "Map.h"
#include "main.h"

#define COLONNE 5
#define LIGNE 4


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
    int fin = 0;
    char **test_grille;
    int pos_joueur_x = 0;
    int pos_joueur_y = 0;
    MAE_Global GameState = INIT;
    MAE_Deplacement deplacementState;


    switch (GameState){
        case INIT:
            Initialisation();
            GameState = AQUISITION_CLAVIER;
            break;
        case AQUISITION_CLAVIER:
            car = getch();
            //setCase([pos_joueur_x][pos_joueur_y] = ' ';
            switch(car)
            {
                case 'q':
                    movement(
                    fin = 1;
                break;
                case 'i':
                    pos_joueur_x--;
                break;
                case 'k':
                    pos_joueur_x++;
                break;
                case 'j':
                    pos_joueur_y--;
                break;
                case 'l':
                    pos_joueur_y++;
                break;
            }
            GameState = VERIF_VICTOIRE;
            break;
        case VERIF_VICTOIRE:

            break;
        case VICTOIRE:
            break;
        default:
            break;
    }


    //Allouer memoire pour le tableau
    test_grille = (char **)malloc(LIGNE * sizeof(char *));
    for (int i = 0; i < LIGNE; i++) {
        test_grille[i] = (char *)malloc(COLONNE * sizeof(char));
    }

    //Remplissage du tableau
    for(int i=0; i< LIGNE; i++)
    {
        for(int j=0; j<COLONNE; j++)
        {
            test_grille[i][j] = ' ';
        }
    }
    test_grille[pos_joueur_x][pos_joueur_y] = 'j';

    //Affichage du tableau
    grille_print(test_grille, COLONNE, LIGNE);

    while(!fin)
    {
        car = getch();
        test_grille[pos_joueur_x][pos_joueur_y] = ' ';
        switch(car)
        {
            case 'q':
                fin = 1;
                break;
            case 'i':
                pos_joueur_x--; 
                break;
            case 'k':
                pos_joueur_x++; 
                break;
            case 'j':
                pos_joueur_y--; 
                break;
            case 'l':
                pos_joueur_y++; 
                break;
        }
        test_grille[pos_joueur_x][pos_joueur_y] = 'j';
        system("clear");
        grille_print(test_grille, COLONNE, LIGNE);

    }

  
    //Liberation de la memoire pour le tableau
    for (int i = 0; i < LIGNE; i++) {
        free(test_grille[i]);
    }
    free(test_grille);

}

void Initialisation(void)
{
    PlayerInit();
    system("clear");
    printf("Bienvenue dans le jeu\n");
    printf("Pour vous deplacer utilisez les touches suivantes:\n");
    printf("i pour monter\n");
    printf("k pour descendre\n");
    printf("j pour aller a gauche\n");
    printf("l pour aller a droite\n");
    printf("q pour quitter\n");
}




