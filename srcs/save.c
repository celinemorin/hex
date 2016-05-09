/*############################################################################
##																			##
##																			##	
##		module : save.c														##
##																			##
##																			##
##		dependances : error.c, memory.c, gestion_tours.c					##
##																			##
##																			##
############################################################################*/

#include "save.h"
#include "error.h"
#include "memory.h"
#include "gestion_tours.h"

/* rôle : supprimer le fichier contenant l'historique. */

void delete_save (void)
{
	if (remove("historique.txt") != 0)
		error("remove delete_save", 5);
}

/*	rôle : inscris dans un fichier historique.txt le dernier coup joué.
	int X : abscisse.
	int Y : ordonnée.
	State color : couleur du pion. */

void make_save (int X, int Y, State color)
{
	FILE *file = fopen("historique.txt", "a");
	if (file == NULL)
		error("fopen make_save", 6);
	fprintf(file, "%d %d %d\n", color, X, Y);
	fclose(file);
}

/*	rôle : charger une sauvegarde.
	retour : la structure Infos contenant la partie chargée. */

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

/*	rôle : annuler le dernier coup joué.
	Infos infos : la structure à modifier.
	retour : la structure Infos modifiée. */

Infos cancel_coup (Infos infos)
{
	if (system("sed '$d' historique.txt > tmp.txt && rm historique.txt && mv tmp.txt historique.txt") == -1)
		error("system cancel_coup", 8);
	infos = load_save();
	return (infos);
}

/*	rôle : renvoie la ième ligne de l'historique en partant de la fin. 
	int nb : le numéro de la ligne (en partant du bas du fichier).
	retour : tableau vide si la ligne n'existe pas, sinon tableau contenant les valeurs du coup demandé : couleur, X, Y. */

int *historique (int nb)
{
	int *tab = initialisation_tableau(3);
	char commande[36];
	sprintf(commande, "tail -n %d historique.txt > tmp.txt", nb);
	FILE *file1 = fopen("historique.txt", "r");
	if (file1 == NULL)
		error("fopen historique", 12);
	if (ftell(file1) != 0)
	{
		if (system(commande) == -1)
			error("system historique", 9);
		FILE *file2 = fopen("tmp.txt", "r");
		if (file2 == NULL)
			error("fopen historique", 10);
		fscanf(file2, "%d %d %d\n", &tab[0], &tab[1], &tab[2]);
		fclose(file2);
		if (remove("tmp.txt") != 0)
			error("remove historique", 11);
	}
	fclose(file1);
	fclose(file2);
	return (tab);
}
