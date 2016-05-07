#include "unionfind.h"
#include "memory.h"

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

bool nodes_linked (struct uf_node *root, int X1, int Y1, int X2, int Y2)
{
	struct uf_node *a = find_node(root, get_ID(X1, Y1));
	struct uf_node *b = find_node(root, get_ID(X2, Y2));
	bool link = false;
	if (a->group == b->group)
		link = true;
	return (link);
}

static void insert_ID (struct uf_node *root, struct uf_node *temp)
{
	if (temp->ID < root->ID) 
	{
		if (root->left == NULL)
			root->left = temp;
		else
			insert_ID(root->left, temp);
	}
	else
	{
		if (root->right == NULL)
			root->right = temp;
		else
			insert_ID(root->right, temp);
	}
}

struct uf_node *uf_node_add (struct uf_node *root, int X, int Y)
{
	struct uf_node *temp = uf_node_create(X, Y);
	insert_ID(root, temp);
	return (temp);
}

void uf_union (struct uf_node *root, int ID1, int ID2)
{
	struct uf_node *a = find_node(root, ID1);
	struct uf_node *b = find_node(root, ID2);
	if (a->group != b->group)
	{
		if (a->ID > b->ID)
			a->group = b->group;
		else
			b->group = a->group;
	}
}
