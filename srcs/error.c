/*############################################################################
##																			##
##																			##	
##		module : error.c													##
##																			##
##																			##
##		dependances : none													##
##																			##
##																			##
############################################################################*/

#include "error.h"

/*	rôle : affiche un message d'erreur et quitte le programme.
	char *reason : la raison de l'arrêt du programme.
	int val : la valeur donnée à exit() pour quitter le programme. */

void error(char *reason, int val)
{
	perror(reason);
	exit(val);
}