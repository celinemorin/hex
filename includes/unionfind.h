#ifndef __UNIONFIND_H__
#define __UNIONFIND_H__

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct uf_node
{
	int ID;
	struct uf_node *group;
	struct uf_node *left;
	struct uf_node *right;
} uf_node;

//static struct uf_node *find_node (struct uf_node *root, int ID);
int get_ID (int X, int Y);
struct uf_node *uf_node_create (int X, int Y);
int uf_find (struct uf_node *root, int ID);
struct uf_node *uf_node_add (struct uf_node *root, int X, int Y);
bool uf_union (struct uf_node *root, int ID1, int ID2);

#endif
