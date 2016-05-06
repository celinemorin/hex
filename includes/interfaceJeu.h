#ifndef INTERFACEJEU_H
#define INTERFACEJEU_H

#include "interface.h"

Axe recuperationCellule(Axe position);
Axe attente_evenement_jeu(SDL_Surface *ecran);
void creation_interface_jeu(SDL_Surface *ecran,int numMenu);

#endif