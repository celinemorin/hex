/*############################################################################
##																			##
##																			##	
##		module : gestion_tours.c											##
##																			##
##																			##
##		dependances : unionfind.c											##
##																			##
##																			##
############################################################################*/

#include "gestion_tours.h"
#include "unionfind.h"

/*	rôle : ajouter deux nodes adjacentes à un même chemin via leurs pointeurs group.
	Infos infos : la structure à modifier.
	int X1 : l'abcisse de la node 1.
	int Y1 : l'ordonnée de la node 1.
	int X2 : l'abcisse de la node 2.
	int Y2 : l'abcisse de la node 2. */

static void add_adjacent (Infos infos, int X1, int Y1, int X2, int Y2, State color)
{
	if (!(X2 < 1 || X2 > 11 || Y2 < 1 || Y2 > 11 || infos->plateau[X2 - 1][Y2 - 1] != color))
	{
		if (color == red)
			uf_union(infos->red_root, get_ID(X1, Y1), get_ID(X2, Y2));
		else if (color == blue)
			uf_union(infos->blue_root, get_ID(X1, Y1), get_ID(X2, Y2));
	} 
}

/*	rôle : fonction de base pour ajouter un pion dans le jeu + vérifier la validité des coups.
	Infos infos : la structure à modifier.
	int X : abcisse du pion joué.
	int Y : ordonnée du pion joué.
	State color : couleur du joueur qui joue (red ou blue).
	retour : TRUE si le pion a pu être ajouté, FALSE si sa position n'est pas valide. */

bool add_pion (Infos infos, int X, int Y, State color)
{
	bool success = 1;
	if (infos->plateau == NULL || infos->plateau[X - 1][Y - 1] != empty)
		success = 0;
	else
	{
		infos->plateau[X - 1][Y - 1] = color;
		if (color == red)
			uf_node_add(infos->red_root, X, Y);
		else if (color == blue)
			uf_node_add(infos->blue_root, X, Y);
		add_adjacent(infos, X, Y, X, Y - 1, color);
		add_adjacent(infos, X, Y, X + 1, Y - 1, color);
		add_adjacent(infos, X, Y, X - 1, Y, color);
		add_adjacent(infos, X, Y, X + 1, Y, color);
		add_adjacent(infos, X, Y, X - 1, Y + 1, color);
		add_adjacent(infos, X, Y, X, X + 1, color);
	}
	return (success);
}

/*	rôle : définir si le joueur 1 ou 2 a gagné en jouant son pion.
	Infos infos : le jeu en cours à examiner.
	State color : la couleur du joueur qui vient de jouer.
	retour : TRUE si le joueur qui vient de jouer a gagné, false si personne n'a gagné. */

bool end_of_game (Infos infos, State color)
{
	int j, i = 1;
	bool end = false;
	if (color == red)
	{
		while (i <= SIZE && !end)
		{
			if (infos->plateau[SIZE - 1][i - 1] == red)
			{
				j = 1;
				while (j <= SIZE && !end)
				{
					if (infos->plateau[0][j - 1] == red)
						end = nodes_linked(infos->red_root, SIZE, i, 1, j);
					j++;
				}
			}
			i++;
		}
	}
	else if (color == blue)
	{
		while (i <= SIZE && !end)
		{
			if (infos->plateau[i - 1][SIZE - 1] == blue)
			{
				j = 1;
				while (j <= SIZE && !end)
				{
					if (infos->plateau[j - 1][0] == blue)
						end = nodes_linked(infos->blue_root, i, SIZE, j, 1);
					j++;
				}
			}
			i++;
		}
	}
	return (end);
}
