#ifndef INTERFACEJEU_H
#define INTERFACEJEU_H

#include "interface.h"
#include "types.h"

Axe recuperationCellule(Axe position);
void placement_pion(SDL_Surface *ecran, Axe position, int couleur);
void affichageGeneral(SDL_Surface *ecran, Infos varInfo);
Axe attente_evenement_jeu(SDL_Surface *ecran, Infos varInfo, int joueur);
void creation_interface_jeu(SDL_Surface *ecran,int numMenu);

#endif