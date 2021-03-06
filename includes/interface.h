#ifndef INTERFACE_H
#define INTERFACE_H

#include "menu.h"
#include "types.h"
#include "save.h"

Axe recuperationCellule(Axe position);
void placement_pion(SDL_Surface *ecran, Axe position, int couleur);
void affichageGeneral(SDL_Surface *ecran, Infos varInfo);
void interfaceHistorique(SDL_Surface *ecran, Infos varInfo);
Axe attente_evenement_jeu(SDL_Surface *ecran, Infos varInfo, int joueur);
void creation_interface_jeu(SDL_Surface *ecran,int numMenu);

#endif
