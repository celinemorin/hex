#ifndef __UNIONFIND_H__
#define __UNIONFIND_H__

#include <stdbool.h>
#include <stdio.h>
#include "types.h"

int get_ID (int X, int Y);
struct uf_node *uf_node_add (struct uf_node *root, int X, int Y);
bool nodes_linked (struct uf_node *root, int X1, int Y1, int X2, int Y2);
void uf_union (struct uf_node *root, int ID1, int ID2);

#endif