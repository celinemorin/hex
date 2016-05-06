#ifndef __UNIONFIND_H__
#define __UNIONFIND_H__

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct uf_node
{
	int ID;
	struct uf_node *group;
	struct uf_node *left;
	struct uf_node *right;
} uf_node;

typedef struct unionfind *UnionFind;

#endif
