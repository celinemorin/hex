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
	destroy_unionfind_node(infos->red_root);
	destroy_unionfind_node(infos->blue_root);
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
	infos->red_root = uf_node_create(SIZE / 2, SIZE / 2);
	infos->blue_root = uf_node_create(SIZE / 2, SIZE / 2);
	infos->plateau = initialisation_plateau();
	return (infos);
}

void add_adjacent (Infos infos, int X1, int Y1, int X2, int Y2, State color)
{
	bool valid = true;
	if (!(X2 < 1 || X2 > 11 || Y2 < 1 || Y2 > 11 || infos->plateau[X2 - 1][Y2 - 1] != color))
	{
		if (color == red)
			uf_union(infos->red_root, get_ID(X1, Y1), get_ID(X2, Y2));
		else if (color == blue)
			uf_union(infos->blue_root, get_ID(X1, Y1), get_ID(X2, Y2));
	} 
}

void add_pion (Infos infos, int X, int Y, State color)
{
	if (infos->plateau == NULL || infos->plateau[X - 1][Y - 1] != empty)
		exit(1);
	infos->plateau[X - 1][Y - 1] = color;
	if (color == red)
		uf_node_add(infos->red_root, X, Y);
	else if (color == blue)
		uf_node_add(infos->blue_root, X, Y);
	add_adjacent(X, Y, X, Y - 1);
	add_adjacent(X, Y, X + 1, Y - 1);
	add_adjacent(X, Y, X - 1, Y);
	add_adjacent(X, Y, X + 1, Y);
	add_adjacent(X, Y, X - 1, Y + 1);
	add_adjacent(X, Y, X, X + 1);
}

bool end_of_game (Infos infos, State color)
{
	int i = 0;
	bool end = false;
	if (color == red)
	{
		while (i < SIZE && !end)
		{
			if (infos->plateau[i][SIZE - 1] == red)
			{
				j = 0;
				while (j < SIZE && !end)
				{
					if (infos->plateau[j][0] == red)
						end = nodes_linked(infos->red_root, i, SIZE - 1, j, 0);
					j++;
				}
			}
			i++;
		}
	}
	else if (color == blue)
	{
		while (i < SIZE && !end)
		{
			if (infos->plateau[SIZE - 1][i] == blue)
			{
				j = 0;
				while (j < SIZE && !end)
				{
					if (infos->plateau[0][j] == blue)
						end = nodes_linked(infos->blue_root, SIZE - 1, i, 0, j);
					j++;
				}
			}
			i++;
		}
	}
	return (end);
}

int main (int argc, char **argv)
{
	Infos infos = initialisation_infos();
	
	return (0);
}
