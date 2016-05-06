#include "unionfind.h"

static struct uf_node *find_helper (struct uf_node *root, int ID)
{
	struct uf_node *temp = root;
	bool found = false;
	while (temp != NULL && !found) 
	{
		if (temp->ID == ID)
			found = true;
		else if (temp->ID > ID)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return (temp);
}

static struct uf_node *find_node (struct uf_node *root, int ID)
{
	struct uf_node *temp = find_helper(root, ID);
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

int uf_find (struct uf_node *root, int ID)
{
	struct uf_node *group_rep = find_node(root, ID);
	if (group_rep != NULL)
		ID = group_rep->ID;
	return (ID);
}

int get_ID (int X, int Y)
{
	int i, j, ID = 0;
	for (i = 0 ; i < X ; i++)
	{
		for (j = 0 ; j < Y ; j++)
			ID++;
	}
	return (ID);
}

void insert_vertex (struct uf_node *root, struct uf_node *temp)
{
	if (temp->ID < root->ID) 
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

struct uf_node *uf_node_create (int X, int Y)
{
	struct uf_node *temp = malloc(sizeof(struct uf_node));
	if (temp == NULL)
	{
		fprintf(stderr, "malloc in unionfind.c");
		exit(1);
	}
	temp->left = NULL;
	temp->right = NULL;
	temp->ID = get_ID(X, Y);
	temp->group = temp;
	return (temp);
}

struct uf_node *uf_node_add (struct uf_node *root, int X, int Y)
{
	struct uf_node *temp = uf_node_create(X, Y);
	insert_vertex(root, temp);
	return (temp);
}

bool uf_union (struct uf_node *root, int ID1, int ID2)
{
	struct uf_node *a = find_node(root, ID1);
	struct uf_node *b = find_node(root, ID2);
	bool same_group = false;
	if (a->group != b->group)
	{
		if (a->ID > b->ID)
			a->group = b->group;
		else
			b->group = a->group;
	}
	else
		same_group = true;
	return (same_group);
}
