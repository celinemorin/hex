#include "save.h"

void delete_save (void)
{
	if (remove("historique.txt") != 0)
		exit(1);
}

void make_save (int X, int Y, State color)
{
	FILE *file = fopen("historique.txt", "a");
	if (file == NULL)
		exit(1);
	fprintf(file, "%d %d %d\n", color, X, Y);
	fclose(file);
}

void load_save (Board plateau)
{
	int X, Y;
	State color;
	FILE *file = fopen("historique.txt", "r");
	free_plateau(plateau);
	plateau = initialisation_plateau();
	if (file == NULL)
		exit(1);
	while (fscanf(file, "%d %d %d\n", &color, &X, &Y) == 3)
		plateau[X - 1][Y - 1] = color;
	fclose(file);
}

void cancel_coup (Board plateau)
{
	if (system("sed '$d' historique.txt > tmp.txt && rm historique.txt && mv tmp.txt historique.txt") == -1)
		exit(1);
	load_save(plateau);
}