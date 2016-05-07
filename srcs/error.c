#include "error.h"

void error(char *reason, int val)
{
	perror(reason);
	exit(val);
}