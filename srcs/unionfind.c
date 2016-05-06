#include "unionfind.h"
#include <stdlib.h>
#include <assert.h>

typedef struct uf_node
{
	GraphVertex val;
	struct uf_node *group;
	struct uf_node *left;
	struct uf_node *right;
} uf;

typedef struct unionfind
{
	struct uf_node *root;
} unionfind;

UnionFind uf_create (void)
{
	UnionFind new_unionfind = malloc(sizeof(struct unionfind));
	if (new_unionfind == NULL)
	{
		fprintf(stderr, "malloc in unionfind.c");
		exit(1);
	}
	new_unionfind->root = NULL;
	return (new_unionfind);
}

void destroy_unionfind_node (struct uf_node *to_delete)
{
	if (to_delete == NULL)
		return;
	destroy_unionfind_node(to_delete->left);
	destroy_unionfind_node(to_delete->right);
	free(to_delete);
}

void uf_destroy (UnionFind *uf)
{
	assert(uf != NULL);
	if (*uf == NULL)
		return;
	destroy_unionfind_node((*uf)->root);
	free(*uf);
	*uf = NULL;
}

static struct uf_node *find_helper (UnionFind uf, GraphVertex key)
{
	assert(uf != NULL);
	struct uf_node *temp = uf->root;
	bool found = false;
	while (temp != NULL && !found) 
	{
		if (temp->val == key)
			found = true;
		else if (temp->val > key)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return (temp);
}

static struct uf_node *find_node (UnionFind uf, GraphVertex key)
{
	assert(uf != NULL);
	struct uf_node *temp = find_helper(uf, key);
	if (temp != NULL)
	{
		while (temp->group != temp)
		{
			temp->group = temp->group->group;
			temp = temp->group;
		}
	}
	return (temp);
}

GraphVertex uf_find (UnionFind uf, GraphVertex vertex)
{
	struct uf_node *group_rep = find_node(uf, vertex);
	if (group_rep != NULL)
		vertex = group_rep->val;
	return (vertex);
}

struct uf_node *uf_node_create (GraphVertex val)
{
	struct uf_node *temp = malloc(sizeof(struct uf_node));
	if (temp == NULL)
	{
		fprintf(stderr, "malloc in unionfind.c");
		exit(1);
	}
	temp->left = NULL;
	temp->right = NULL;
	temp->val = val;
	temp->group = temp;
	return (temp);
}

void insert_vertex (struct uf_node *root, struct uf_node *temp)
{
	if (temp->val < root->val) 
	{
		if (root->left == NULL)
			root->left = temp;
		else
			insert_vertex(root->left, temp);
	}
	else
	{
		if (root->right == NULL)
			root->right = temp;
		else
			insert_vertex(root->right, temp);
	}
}

bool uf_union (UnionFind uf, GraphVertex vertex_a, GraphVertex vertex_b)
{
	assert(uf != NULL);
	struct uf_node *a = find_helper(uf, vertex_a);
	struct uf_node *b = find_helper(uf, vertex_b);
	bool same_group = false;
	if (a == NULL)
	{
		a = uf_node_create(vertex_a);
		if (uf->root == NULL)
			uf->root = a;
		else
			insert_vertex(uf->root, a);
	}
	if (b == NULL)
	{
		b = uf_node_create(vertex_b);
		if (uf->root == NULL)
			uf->root = b;
		else
			insert_vertex(uf->root, b);
	}
	a = find_node(uf, vertex_a);
	b = find_node(uf, vertex_b);
	if (a->group != b->group)
	{
		if (a->val > b->val)
			a->group = b->group;
		else
			b->group = a->group;
	}
	else
		same_group = true;
	return (same_group);
}
