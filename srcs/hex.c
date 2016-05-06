#include "hex.h"
#include "save.h"

void affichage (Board plateau)
{
	int i, j;
	printf("\n\n");
	for (i = 0 ; i < SIZE ; i++)
	{
		for (j = 0 ; j < SIZE ; j++)
			printf(" %d   ", plateau[i][j]);
		printf("\n\n");
	}
}

void destroy_unionfind_node (struct uf_node *to_delete)
{
	if (to_delete == NULL)
		return;
	destroy_unionfind_node(to_delete->left);
	destroy_unionfind_node(to_delete->right);
	free(to_delete);
}

void free_plateau (Board plateau)
{
	int i;
	for (i = 0 ; i < SIZE ; i++)
		free(plateau[i]);
	free(plateau);
}

void free_infos (Infos infos)
{
	free_plateau(infos->plateau);
	destroy_unionfind_node(infos->root);
	free(infos);
}

Board initialisation_plateau (void)
{
	int i, j;
	Board plateau = malloc(sizeof(State *) * SIZE);
	if (plateau == NULL)
		exit(1);
	for (i = 0 ; i < SIZE ; i++)
	{
		plateau[i] = malloc(SIZE * sizeof(State));
		if (plateau[i] == NULL)
			exit(1);
		for (j = 0 ; j < SIZE ; j++)
			plateau[i][j] = empty;
	}
	return (plateau);
}

Infos initialisation_infos (void)
{
	Infos infos = malloc(sizeof(struct infos));
	infos->root = uf_node_create(6, 6);
	infos->plateau = initialisation_plateau();
	return (infos);
}

bool add_adjacent (Infos infos, int X, int Y, State color)
{
	bool valid = true;
	if (X < 1 || X > 11 || Y < 1 || Y > 11)
		valid = false;
	else if (infos->plateau[X][Y] != color)
		valid = false;
	//else 
		// si l'un ou l'autre n'y sont pas les ajouter + union des deux
	return (valid);
}

void add_pion (Infos infos, int X, int Y, State color)
{
	if (infos->plateau == NULL || infos->plateau[X - 1][Y - 1] != empty)
		exit(1);
	infos->plateau[X - 1][Y - 1] = color;
}

// pour savoir si il y a un gagnant, on check si on a dans un meme chemin un Y = 1 et un Y = 11 pour les rouges, et un X = 1 et un X = 11 pour les bleus

int main (int argc, char **argv)
{
	return (0);
}
