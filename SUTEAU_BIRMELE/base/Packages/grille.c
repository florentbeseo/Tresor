#include <stdio.h> //printf
#include <stdint.h> // uint8_t

void grille_print (char **tab_grille, uint8_t nb_colonne, uint8_t nb_ligne)
{
    for(int j= 0; j<nb_ligne; j++)
    {
        //ligne de delimitation
        for(int i=0; i<nb_colonne; i++)
        {
            printf("+---");
        }
        printf("+\n");
        //ligne de contenu
        for(int i=0; i<nb_colonne; i++)
        {
            printf("| ");
            printf("%c",tab_grille[j][i]); //contenu
            printf(" ");
        }
        printf("|\n");
    }
    //ligne de delimitation
    for(int i=0; i<nb_colonne; i++)
    {
        printf("+---");
    }
    printf("+\n");
}