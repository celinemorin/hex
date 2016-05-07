#include "save.h"
#include "error.h"
#include "memory.h"
#include "gestion_tours.h"

void delete_save (void)
{
	if (remove("historique.txt") != 0)
		error("remove delete_save", 5);
}

void make_save (int X, int Y, State color)
{
	FILE *file = fopen("historique.txt", "a");
	if (file == NULL)
		error("fopen make_save", 6);
	fprintf(file, "%d %d %d\n", color, X, Y);
	fclose(file);
}

Infos load_save (void)
{
	int X, Y;
	State color;
	Infos infos = initialisation_infos();
	FILE *file = fopen("historique.txt", "r");
	if (file == NULL)
		error("fopen load_save", 7);
	while (fscanf(file, "%d %d %d\n", &color, &X, &Y) == 3)
		add_pion(infos, X, Y, color);
	fclose(file);
	return (infos);
}

Infos cancel_coup (Infos infos)
{
	if (system("sed '$d' historique.txt > tmp.txt && rm historique.txt && mv tmp.txt historique.txt") == -1)
		error("system cancel_coup", 8)
	infos = load_save();
	return (infos);
}
