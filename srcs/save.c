#include "save.h"

void delete_save (void)
{
	FILE *file = fopen("historique.txt", "w");
	if (file == NULL)
		exit(1);
	fclose(file);
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
	if (file == NULL)
		exit(1);
	while (fscanf(file, "%d %d %d\n", &color, &X, &Y) == 3)
		plateau[X - 1][Y - 1] = color;
	fclose(file);
}

void cancel_coup (Board plateau)
{
	if (system("tail -r historique.txt | tail +2 | tail -r > historique.txt") == -1)
		exit(1);
	load_save(plateau);
}