#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define SIZE 11


int *initialisation_tableau (int size);
Board initialisation_plateau (void);
struct uf_node *uf_node_create (int X, int Y);
Infos initialisation_infos (void);
void free_plateau (Board plateau);
void destroy_unionfind_node (struct uf_node *to_delete);
void free_infos (Infos infos);

#endif