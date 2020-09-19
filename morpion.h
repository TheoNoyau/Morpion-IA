#ifndef MORPION_H
#define MORPION_H
#define SIZE 1000

//typedef char morpion[SIZE][SIZE];
typedef char **morpion ;

// Affiche dans la console la grille de morpion
void afficherGrille (morpion jeu, int size) ;

// Initialise la grille de morpion avec des -1
char ** initGame (int size) ;

// En fonction des coordonnées i et j joue un 0 ou 1. Renvoie 1 si le joueur doit rejouer, 0 sinon
int jouer (morpion jeu, int i, int j, char player, int size) ;

// Renvoie 1 si player a gagné le jeu
int gagnant (morpion jeu, char player, int size) ;

// Renvoie le nombre de cases vides sur une grille (-1)
int casesVides (morpion jeu, int size);

int max (morpion jeu, int size) ;

int min (morpion jeu, int size) ;

void MinMax (morpion jeu, int size, int *i, int *j) ;

int max_AB(morpion jeu, int size, int alpha, int beta, int prodondeur);

int min_AB(morpion jeu, int size, int alpha, int beta, int profondeur);

void MinMax_AB(morpion jeu, int size, int *ii, int *jj, int alpha, int beta, int profondeur);

int alphabeta(morpion jeu, int size, int alpha, int beta, int *ii, int *jj, int isMax);

#endif





