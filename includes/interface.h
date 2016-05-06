#ifndef INTERFACE_H
#define INTERFACE_H

#define HAUTEUR 600 
#define LARGEUR 800  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
 
#include <SDL/SDL.h>
#include <SDL/SDL_keysym.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
  
#define POSX 100
#define POSJOUERY 200
#define POSCHARGY 300
#define POSQUITY 450

#define POSHVHY 200
#define POSHV1Y 300
#define POSHV2Y 400
#define POSRETOURY 500

#define POSJEUY 175

#define JOUER 1
#define CHARGEMENT 2
#define QUITTER 3
#define RETOUR 4
#define NEWGAME 5

typedef struct
{
    int x, y;
}Axe;

typedef struct
{
    int h, w;
}Dimensions;

void chargementUneImage(SDL_Surface *ecran, char * emplacement,int x,int y);
void initialisationImage(SDL_Surface *ecran, int numeroMenu);
void souriPos(SDL_Surface *ecran,Axe pos,int numeroMenu);
int attente_evenement_menu(SDL_Surface *ecran, int numeroMenu);
int creation_interface(SDL_Surface *ecran,int numMenu);

#endif