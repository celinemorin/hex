#ifndef __HEX_H__
#define __HEX_H__

#include <stdlib.h>

#define SIZE 11

typedef enum state {empty, red, blue} State;
typedef State **Board;

typedef struct node
{
	int X, Y;
	struct node *next;
} node;

typedef struct node *Node;

Board initialisation_plateau (void);
void free_plateau (Board plateau);

#endif