#include <stdio.h>
#include <stdbool.h>
#include "types.h"
#include "unionfind.h"
#include "gestion_tours.h"
#include "save.h"
#include "memory.h"

int main (void)
{
	// Unité 0 memory init
	
	Infos infos = initialisation_infos(infos);
	struct uf_node *a = uf_node_create(1, 1);
	int i, j;
	bool res = false;
	
	// Unité 1 gestion_tours
	
	res = add_pion(infos, 2, 2, red);
	printf("ADD X = 2 Y = 2 ROUGE : %s\n", res ? "true" : "false");
	res = add_pion(infos, -1, 3, blue);
	printf("ADD X = -1 Y = 3 BLEU : %s\n", res ? "true" : "false");	
	res = add_pion(infos, 2, 2, blue);
	printf("ADD X = 2 Y = 2 BLEU : %s\n", res ? "true" : "false");
	res = add_pion(infos, 2, 2, red);
	printf("ADD X = 2 Y = 2 ROUGE : %s\n", res ? "true" : "false");
	res = add_pion(infos, 1, 12, blue);
	printf("ADD X = 1 Y = 12 BLEU : %s\n", res ? "true" : "false");
	res = add_pion(infos, 1, 7, blue);
	printf("ADD X = 1 Y = 7 BLEU : %s\n", res ? "true" : "false");
	res = add_pion(infos, 3, 6, red);
	printf("ADD X = 3 Y = 6 ROUGE : %s\n", res ? "true" : "false");
	
	// Unité 2 save
	
	printf("SAVE X = 2 Y = 2 ROUGE\n");
	make_save(2, 2, rouge);
	printf("SAVE X = 1 Y = 7 BLEU\n");
	make_save(1, 7, rouge);
	printf("SAVE X = 3 Y = 6 ROUGE\n");
	make_save(3, 6, rouge);
	
	// Unité 3 unionfind
	
	a = find_helper(infos->red_root, get_ID(2, 2));
	if (a == NULL)
		printf("SEARCH X = 2 Y = 2 ROUGE : KO\n");
	else
		printf("SEARCH X = 2 Y = 2 ROUGE : OK\n");
	a = find_helper(infos->red_root, get_ID(7, 8));
	if (a == NULL)
		printf("SEARCH X = 7 Y = 8 ROUGE : KO\n");
	else
		printf("SEARCH X = 7 Y = 8 ROUGE : OK\n");
	
	// Unité 4 memory free
	
	printf("Tableau actuel :\n\n");
	for (i = 0 ; i < 11, i++)
	{
		for (j = 0 ; j < 11, j++)
			printf("  %d   ", infos->plateau[i][j]);
		printf("\n");
	}
	free_infos(infos);
	printf("FREE Tableau et structure :\n\n");
	for (i = 0 ; i < 11, i++)
	{
		for (j = 0 ; j < 11, j++)
			printf("  %d   ", infos->plateau[i][j]);
		printf("\n");
	}
		
	// Unité 5 load
	
	printf("LOAD PARTIE SAVED :\n\n");
	infos = load_save();
	for (i = 0 ; i < 11, i++)
	{
		for (j = 0 ; j < 11, j++)
			printf("  %d   ", infos->plateau[i][j]);
		printf("\n");
	}
	
	// Unité 6 cancel
	
	printf("CANCEL DERNIER COUP :\n\n");
	free_infos(infos);
	infos = cancel_coup(infos);
	for (i = 0 ; i < 11, i++)
	{
		for (j = 0 ; j < 11, j++)
			printf("  %d   ", infos->plateau[i][j]);
		printf("\n");
	}
	
	// Unité 7 union
	
	res = add_pion(infos, 10, 10, red);
	printf("ADD X = 10 Y = 10 ROUGE : %s\n", res ? "true" : "false");
	res = add_pion(infos, 7, 8, red);
	printf("ADD X = 7 Y = 8 ROUGE : %s\n", res ? "true" : "false");
	res = nodes_linked(infos->red_root, 10, 10, 7, 8);
	printf("NODES LINKED ? : %s\n", res ? "true" : "false");
	res = add_pion(infos, 11, 10, blue);
	printf("ADD X = 11 Y = 10 BLEU : %s\n", res ? "true" : "false");
	res = nodes_linked(infos->red_root, 10, 10, 11, 10);
	printf("NODES LINKED ? : %s\n", res ? "true" : "false");
	res = add_pion(infos, 9, 10, red);
	printf("ADD X = 9 Y = 10 ROUGE : %s\n", res ? "true" : "false");
	res = nodes_linked(infos->red_root, 10, 10, 9, 10);
	printf("NODES LINKED ? : %s\n", res ? "true" : "false");
	
	//
	
	free(a);
	free_infos(infos);
	return (0);
}