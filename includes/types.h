#ifndef __TYPES_H__
#define __TYPES_H__

typedef enum state {empty, red, blue} State;
typedef State **Board;

typedef struct uf_node
{
	int ID;
	struct uf_node *group;
	struct uf_node *left;
	struct uf_node *right;
} uf_node;

typedef struct infos
{
	Board plateau;
	struct uf_node *red_root;
	struct uf_node *blue_root;
} infos;

typedef struct infos *Infos;

#endif
