##############################################################################
##																			##
##																			##	
##		module : unionfind.c												##
##																			##
##		auteur : celine morin												##
##																			##
##		dependances : memory.c												##
##																			##
##																			##
##############################################################################

#include "unionfind.h"
#include "memory.h"

/* 	rôle : trouver la node contenant l'ID donné en paramètre.
	struct uf_node *root : racine de l'arbre où rechercher la node.
	int ID : ID à trouver.
	etour : la node demandée si celle-ci est trouvée, NULL sinon. */

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

/* 	rôle : trouver la node contenant l'ID donné en paramètre, puis trouver la node du représentant de son groupe.
	struct uf_node *root : racine de l'arbre où rechercher la node.
	int ID : ID à trouver.
	retour : la node représentatrice du groupe de la node ID si celle-ci est trouvée, NULL sinon.. */

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

/*	rôle : calculer l'ID unique de la node située aux coordonnées (X, Y).
	int X : abcisse.
	int Y : ordonnée.
	retour : l'ID trouvé pour le point (X, Y). */

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

/*	rôle : définir si deux points font partie d'un même chemin (c'est-à-dire si ils ont la même node représentatrice).
	struct uf_node *root : racine de l'arbre où rechercher les nodes.
	int X1 : abcisse de la node 1.
	int Y1 : ordonnée de la node 1.
	int X2 : abcisse de la node 2.
	int Y2 : ordonnée de la node 2.
	retour : TRUE si les deux nodes font partie du même chemin, FALSE sinon. */

bool nodes_linked (struct uf_node *root, int X1, int Y1, int X2, int Y2)
{
	struct uf_node *a = find_node(root, get_ID(X1, Y1));
	struct uf_node *b = find_node(root, get_ID(X2, Y2));
	bool link = false;
	if (a->group == b->group)
		link = true;
	return (link);
}

/*	rôle : insérer une nouvelle node dans l'arbre.
	struct uf_node *root : racine de l'arbre où insérer la node.
	struct uf_node *temp : la node à insérer. */

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

/* 	rôle : créer une nouvelle node puis l'ajouter à la racine donnée en paramètre.
	struct uf_node *root : racine de l'arbre où insérer la node.
	int X : abscisse de la node.
	int Y : ordonnée de la node.
	retour : la node ajoutée. */

struct uf_node *uf_node_add (struct uf_node *root, int X, int Y)
{
	struct uf_node *temp = uf_node_create(X, Y);
	insert_ID(root, temp);
	return (temp);
}

/* 	rôle : unir deux nodes adjacentes par leur pointeur group.
	struct uf_node *root : racine de l'arbre où modifier le groupe des nodes.
	int ID1 : ID de la node 1.
	int ID2 : ID de la node 2. */

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
