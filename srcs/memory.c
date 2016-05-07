#include "memory.h"
#include "unionfind.h"
#include "error.h"

Board initialisation_plateau (void)
{
	int i, j;
	Board plateau = malloc(sizeof(State *) * SIZE);
	if (plateau == NULL)
		error("malloc initialisation_plateau", 1);
	for (i = 0 ; i < SIZE ; i++)
	{
		plateau[i] = malloc(SIZE * sizeof(State));
		if (plateau[i] == NULL)
			error("malloc initialisation_plateau", 2);
		for (j = 0 ; j < SIZE ; j++)
			plateau[i][j] = empty;
	}
	return (plateau);
}

struct uf_node *uf_node_create (int X, int Y)
{
	struct uf_node *temp = malloc(sizeof(struct uf_node));
	if (temp == NULL)
		error("malloc uf_node_create", 3);
	temp->left = NULL;
	temp->right = NULL;
	temp->ID = get_ID(X, Y);
	temp->group = temp;
	return (temp);
}

Infos initialisation_infos (void)
{
	Infos infos = malloc(sizeof(struct infos));
	if (infos == NULL)
		error("malloc initialisation_infos", 4);
	infos->red_root = uf_node_create(SIZE / 2, SIZE / 2);
	infos->blue_root = uf_node_create(SIZE / 2, SIZE / 2);
	infos->plateau = initialisation_plateau();
	return (infos);
}

void free_plateau (Board plateau)
{
	int i;
	for (i = 0 ; i < SIZE ; i++)
		free(plateau[i]);
	free(plateau);
}

void destroy_unionfind_node (struct uf_node *to_delete)
{
	if (to_delete == NULL)
		return;
	destroy_unionfind_node(to_delete->left);
	destroy_unionfind_node(to_delete->right);
	free(to_delete);
}

void free_infos (Infos infos)
{
	free_plateau(infos->plateau);
	destroy_unionfind_node(infos->red_root);
	destroy_unionfind_node(infos->blue_root);
	free(infos);
}
