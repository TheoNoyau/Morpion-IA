#ifndef MORPION_SDL_H
#define MORPION_SDL_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "morpion.h"

// Change la couleur de la fenêtre
int setWindowColor(SDL_Renderer *renderer, SDL_Color color) ;

// Change la couleur de rendu
int setColor(SDL_Renderer *renderer, SDL_Color color);

// Dessine un bouton aux coordonnées x et y et de largeur w et de hauteur h
int drawButton (SDL_Renderer *renderer, SDL_Color color, int x, int y, int w, int h, char text[]) ;

// Dessine une case vide
int drawCase(SDL_Renderer *renderer, SDL_Color color, int x, int y, int w);

// Test si un click de souris est dans le rectangle aux coordonnées x,y et de taille w*h
int isInCoords(int x, int y, int w, int h, SDL_Event event);

// Récupère la taille N du jeu par une entrée clavier
int askN (SDL_Event event, SDL_Renderer *renderer) ;

// Met dans i et j les coordonnées où a cliqué le joueur
int waitToPlay(int size, SDL_Renderer *renderer, char player, SDL_Event event, int *i, int *j);

// Dessine un carré qui représente le joueur rond
int drawCircle(SDL_Renderer *renderer, int i, int j, int size) ;

// Dessine une Croix
int drawCross(SDL_Renderer *renderer, int i, int j, int size) ;

// Dessine la grille entière
int drawGrille (int size, SDL_Renderer *renderer, morpion jeu) ;

#endif