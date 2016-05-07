#ifndef __UNIONFIND_H__
#define __UNIONFIND_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct uf_node
{
	int ID;
	struct uf_node *group;
	struct uf_node *left;
	struct uf_node *right;
} uf_node;

int get_ID (int X, int Y);
struct uf_node *uf_node_create (int X, int Y);
struct uf_node *uf_node_add (struct uf_node *root, int X, int Y);
bool nodes_linked (struct uf_node *root, int X1, int Y1, int X2, int Y2);
bool uf_union (struct uf_node *root, int ID1, int ID2);

#endif
