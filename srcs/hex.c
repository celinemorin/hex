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
	if (!(X2 < 1 || X2 > 11 || Y2 < 1 || Y2 > 11 || infos->plateau[X2 - 1][Y2 - 1] != color))
	{
		if (color == red)
			uf_union(infos->red_root, get_ID(X1, Y1), get_ID(X2, Y2));
		else if (color == blue)
			uf_union(infos->blue_root, get_ID(X1, Y1), get_ID(X2, Y2));
	} 
}

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

int main (int argc, char **argv)
{
	Infos infos = initialisation_infos();
	add_pion(infos, 5, 1, blue);
	make_save(5, 1, blue);
	add_pion(infos, 5, 2, blue);
	make_save(5, 2, blue);	
    add_pion(infos, 5, 3, blue);
	make_save(5, 3, blue);
	add_pion(infos, 5, 4, blue);
	make_save(5, 4, blue);
	add_pion(infos, 5, 5, blue);
	make_save(5, 5, blue);
	add_pion(infos, 5, 6, blue);
	make_save(5, 6, blue);
	add_pion(infos, 5, 7, blue);
	make_save(5, 7, blue);
	add_pion(infos, 5, 8, blue);
	make_save(5, 8, blue);
	add_pion(infos, 5, 9, blue);
	make_save(5, 9, blue);
	add_pion(infos, 5, 10, blue);
	make_save(5, 10, blue);
	add_pion(infos, 5, 11, blue);
	make_save(5, 11, blue);
	affichage(infos->plateau);
	free_infos(infos);
	infos = cancel_coup(infos);
	//load_save(infos);
	affichage(infos->plateau);
	if (end_of_game(infos, blue))
		printf("OUIIIIII\n");
	free_infos(infos);
	return (0);
}
