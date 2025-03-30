/**
* @file Trap.c
 * @brief Implémentation du module de gestion des pièges.
 *
 * Ce fichier contient les fonctions pour créer, supprimer et gérer les pièges dans le jeu.
 * Les pièges sont placés aléatoirement sur la carte et peuvent interagir avec le joueur.
 *
 * @section description Description des fonctions
 * - Trap_new : Crée un nouveau piège.
 * - Trap_delete : Supprime un piège.
 * - Trap_get_pos : Récupère la position d'un piège.
 * - Trap_get_number : Récupère le numéro d'un piège.
 */

#include <stdlib.h>
#include "Trap.h"
#include "main.h"
#include <time.h>

/**
 * @brief Récupère la position d'un piège.
 * @param trap Pointeur vers le piège.
 * @return Coordonnées du piège.
 */
extern Coordinates Trap_get_pos(Trap *trap) {
	Coordinates pos_Trap;
	pos_Trap.x = trap->position_x;
	pos_Trap.y = trap->position_y;
	return pos_Trap;
}

/**
 * @brief Récupère le numéro d'un piège.
 * @param trap Pointeur vers le piège.
 * @return Numéro du piège.
 */
extern int Trap_get_number(Trap *trap) {
	int numTrap = trap->numTrap;
	return numTrap;
}

static int nbInstances = 0;

/**
 * @brief Crée un nouveau piège.
 * @return Pointeur vers le nouveau piège.
 */
extern Trap *Trap_new() {
	Trap *this = (Trap*)calloc(1, sizeof(Trap)); // Allocation mémoire
	this->numTrap = nbInstances;
	this->position_x = rand() % WIDTH_MAP; // nombre entre 0 et 9
	this->position_y = rand() % HEIGHT_MAP; // nombre entre 0 et 9
	assert(this != NULL); // Vérification de l'allocation
	assert(this->position_x >= 0 && this->position_x < WIDTH_MAP);
	assert(this->position_y >= 0 && this->position_y < HEIGHT_MAP);
	nbInstances++;
	return this;
}

/**
 * @brief Supprime un piège.
 * @param this Pointeur vers le piège à supprimer.
 */
extern void Trap_delete(Trap *this) {
	free((Trap *)this);
}