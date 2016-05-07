/*############################################################################
##																			##
##																			##	
##		module : error.c													##
##																			##
##		auteur : celine morin												##
##																			##
##		dependances : none													##
##																			##
##																			##
############################################################################*/

#include "error.h"

void error(char *reason, int val)
{
	perror(reason);
	exit(val);
}