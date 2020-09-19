#include <stdlib.h>
#include <stdio.h>
#include "morpion.h"

void afficherGrille (morpion jeu, int size) {
    int i, j, k ;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (jeu[i][j] == 0) printf (" O |");
            else if (jeu[i][j] == 1) printf (" X |");
            else printf ("   |");
            
        }
        printf ("\n") ;
        for (k = 0; k < size; k++) {
            printf("____") ;
        }
        printf("\n");
    }
}

char ** initGame (int size) {  
    int i, j ;
    
    char ** jeu = malloc( size*sizeof( char* ));

    for ( i = 0; i < size; i++ )
    {
        jeu[i] = malloc( size );
    }

    for (i = 0; i < size; i ++) {
        for (j = 0; j < size; j++) {
            jeu[i][j] = -1 ;
        }
    } 

    return jeu ;
}

int jouer(morpion jeu, int i, int j, char player, int size)
{
    if (i < 0 || i >= size || j < 0 || j >= size) return 1;
    else if (jeu[i][j] == 0 || jeu[i][j] == 1) return 1;
    else jeu[i][j] = player;
    return 0;
}

int casesVides (morpion jeu, int size) {
    int i, j, n ;

    n = 0 ;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (jeu[i][j] == -1) n++ ;
        }
    }

    return n ;
}

int gagnant (morpion jeu, char player, int size)
{
    int i, j, col, row, diag1, diag2, win;
    win = 0 ;
    
    for (i = 0; i < size && win == 0; i++) {
        if (win == 0) row = 1 ;
        for (j = 0; j < size; j++) {
            row = row && jeu[i][j] == player ;
            win = row;
        }
    }
    for (j = 0; j < size && win == 0; j++){
        if (win == 0) col = 1 ;
        for (i = 0; i < size; i++){
            col = col && jeu[i][j] == player ;
            win = col;
        }
    }

    diag1 = 1;
    diag2 = 1;
    i = 0 ;
    j = 0 ;
    while (i < size && j < size){
        diag1 = diag1 && jeu[i][j] == player;
        diag2 = diag2 && jeu[i][size - j - 1] == player;
        i++;
        j++;
    }

    if (casesVides(jeu, size) == 0 && !(row || col || diag1 || diag2)) return -1 ;
    return (row || col || diag1 || diag2) ;
}

int max (morpion jeu, int size)
{
    int score, i, j, valeur ;

    if (gagnant(jeu, 1, size) == 1) return 10 ;
    else if (gagnant(jeu, 0, size) == 1)  return -10;
    else if (gagnant(jeu, 1, size) == -1) {
        return 0;
    }
    score = -10000 ; //-infini
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (jeu[i][j] == -1) {
                jeu[i][j] = 1 ;
                valeur = min(jeu, size) ;
                if (score < valeur) score = valeur ;     
                jeu[i][j] = -1 ;        
            }
        }
    }
    return score ;
}

int min (morpion jeu, int size)
{
    int score, i, j, valeur ;
    
    if (gagnant(jeu, 1, size) == 1) return 10 ;
    else if (gagnant(jeu, 0, size) == 1) return -10;
    else if (gagnant(jeu, 1, size) == -1) return 0;

    score = 10000 ; //infini
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (jeu[i][j] == -1) {
                jeu[i][j] = 0 ;
                valeur = max(jeu, size) ;
                if (score > valeur) score = valeur ;     
                jeu[i][j] = -1 ;           
            }
        }
    }
    return score ;
}

void MinMax (morpion jeu, int size, int *ii, int *jj)
{
    int i, j, valeur;
    int score = 10000; //infini
  
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            if (jeu[i][j] == -1){
                jeu[i][j] = 0;
                valeur = max(jeu, size);      
                if (score > valeur){
                    score = valeur;
                   *ii = i ;
                   *jj = j ;
                }
                jeu[i][j] = -1;
            }  
        }
    }
}

int max_AB(morpion jeu, int size, int alpha, int beta, int profondeur)
{
    int i, j, valeur;

    if (profondeur == 0) return 0;
    if (gagnant(jeu, 1, size) == 1) return 10 ;
    else if (gagnant(jeu, 0, size) == 1) return -10;
    else if (gagnant(jeu, 1, size) == -1) return 0;

    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            if (jeu[i][j] == -1){
                jeu[i][j] = 1;
                valeur = min_AB(jeu, size, alpha, beta, profondeur - 1);
                jeu[i][j] = -1;
                if (alpha < valeur) alpha = valeur;
                if (beta <= alpha) return alpha;
            }
        }
    }
    return alpha;
}

int min_AB(morpion jeu, int size, int alpha, int beta, int profondeur)
{
    int i, j, valeur;

    if (profondeur == 0) return 0;
    if (gagnant(jeu, 1, size) == 1) return 10 ;
    else if (gagnant(jeu, 0, size) == 1) return -10;
    else if (gagnant(jeu, 1, size) == -1) return 0;

    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            if (jeu[i][j] == -1){
                jeu[i][j] = 0;
                valeur = max_AB(jeu, size, alpha, beta, profondeur - 1);
                jeu[i][j] = -1;
                if (beta > valeur) beta = valeur;
                if (beta <= alpha) return beta;
            }
        }
    }
    return beta;
}

void MinMax_AB(morpion jeu, int size, int *ii, int *jj, int alpha, int beta, int profondeur)
{
    int i, j, valeur;
    
    *ii = -1;
    *jj = -1;
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            if (jeu[i][j] == -1){
                jeu[i][j] = 0;
                valeur = max_AB(jeu, size, alpha, beta, profondeur - 1);
                if (beta > valeur){
                    beta = valeur;
                    *ii = i;
                    *jj = j;
                }
                jeu[i][j] = -1;
            }
        }
    }
}

// int alphabeta(morpion jeu, int size, int alpha, int beta, int *ii, int *jj, int isMax)
// {
//     int i, j, bestVal, valeur;

//     if (gagnant(jeu, 1, size) == 1) return 10 ;
//     else if (gagnant(jeu, 0, size) == 1) return -10;
//     else if (gagnant(jeu, 1, size) == -1) return 0;

//     if (isMax == 1){
//         bestVal = -1000;
//         for (i = 0; i < size; i++){
//             for (j = 0; j < size; j++){
//                 jeu[i][j] = 1;
//                 printf("aaaa\n");
//                 valeur = alphabeta(jeu, size, alpha, beta, ii, jj, 0);
//                 jeu[i][j] = -1;
//                 if (bestVal < valeur) bestVal = valeur;
//                 if (alpha < bestVal) {
//                     alpha = bestVal;
//                     *ii = i;
//                     *jj = j;
//                 }
//                 if (beta <= alpha) return bestVal;
//             }
//         }
//     }
//     else if (isMax == 0){
//         bestVal = 1000;
//         for (i = 0; i < size; i++){
//             for (j = 0; j < size; j++){
//                 jeu[i][j] = 0;
//                 valeur = alphabeta(jeu, size, alpha, beta, ii, jj, 1);
//                 jeu[i][j] = -1;
//                 if (bestVal < valeur) bestVal = valeur;
//                 if (beta < bestVal) beta = bestVal;
//                 if (beta <= alpha) return bestVal;
//             }
//         }
//     }
// }
