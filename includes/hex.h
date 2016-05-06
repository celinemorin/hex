#ifndef __HEX_H__
#define __HEX_H__

#include <stdlib.h>
#include <stdbool.h>
#include "unionfind.h"

#define SIZE 11

typedef enum state {empty, red, blue} State;
typedef State **Board;

typedef struct infos
{
	Board plateau;
	struct uf_node *root;
} infos;

typedef struct infos *Infos;

void free_infos (Infos infos);
Infos initialisation_infos (void);

#endif