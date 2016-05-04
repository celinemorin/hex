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

Board add_pion (Board plateau, int X, int Y, State color)
{
	if (plateau == NULL || plateau[X - 1][Y - 1] != empty)
		exit(1);
	plateau[X - 1][Y - 1] = color;
	return (plateau);
}

Node search_node (Node root, int X, int Y) // root != NULL
{
	Node current_node = root;
	do
	{
		if (current_node->X == X && current_node->Y == Y)
			return (current_node);
		current_node = current_node->next;
	} while (current_node != NULL);
	return (NULL);
}

// faire un root, auquel je relie autant de d'autres root que de passages separes ; si les deux n'existe pas, on cree un nouveau path
// si un des deux existe, on rajoute l'autre a sa suite, si les deux existent on deporte un des deux avec l'autre (realloc size d'un tableau dans le root)
// pour savoir si il y a un gagnant, on check si on a dans un meme chemin un Y = 1 et un Y = 11 pour les rouges, et un X = 1 et un X = 11

int main (int argc, char **argv)
{
	Board plateau = initialisation_plateau();
	/*plateau = add_pion(plateau, 1, 1, red);
	make_save(1, 1, red);
	plateau = add_pion(plateau, 2, 2, blue);
	make_save(2, 2, blue);*/
	load_save(plateau);
	affichage(plateau);
	return (0);
}
