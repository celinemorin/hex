#ifndef __UNIONFIND_H__
#define __UNIONFIND_H__

#include <stdbool.h>

typedef struct unionfind *UnionFind;

UnionFind uf_create(void);
void uf_destroy(UnionFind * uf);
GraphVertex uf_find (UnionFind uf, GraphVertex vertex);
bool uf_union (UnionFind uf, GraphVertex vertex_a, GraphVertex vertex_b);

#endif
