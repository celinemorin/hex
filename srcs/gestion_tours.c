#include "gestion_tours.h"
#include "unionfind.h"

static void add_adjacent (Infos infos, int X1, int Y1, int X2, int Y2, State color)
{
	if (!(X2 < 1 || X2 > 11 || Y2 < 1 || Y2 > 11 || infos->plateau[X2 - 1][Y2 - 1] != color))
	{
		if (color == red)
			uf_union(infos->red_root, get_ID(X1, Y1), get_ID(X2, Y2));
		else if (color == blue)
			uf_union(infos->blue_root, get_ID(X1, Y1), get_ID(X2, Y2));
	} 
}

bool add_pion (Infos infos, int X, int Y, State color)
{
	bool success = 1;
	if (infos->plateau == NULL || infos->plateau[X - 1][Y - 1] != empty)
		success = 0;
	else
	{
		infos->plateau[X - 1][Y - 1] = color;
		if (color == red)
			uf_node_add(infos->red_root, X, Y);
		else if (color == blue)
			uf_node_add(infos->blue_root, X, Y);
		add_adjacent(infos, X, Y, X, Y - 1, color);
		add_adjacent(infos, X, Y, X + 1, Y - 1, color);
		add_adjacent(infos, X, Y, X - 1, Y, color);
		add_adjacent(infos, X, Y, X + 1, Y, color);
		add_adjacent(infos, X, Y, X - 1, Y + 1, color);
		add_adjacent(infos, X, Y, X, X + 1, color);
	}
	return (success);
}

bool end_of_game (Infos infos, State color)
{
	int j, i = 1;
	bool end = false;
	if (color == red)
	{
		while (i <= SIZE && !end)
		{
			if (infos->plateau[SIZE - 1][i - 1] == red)
			{
				j = 1;
				while (j <= SIZE && !end)
				{
					if (infos->plateau[0][j - 1] == red)
						end = nodes_linked(infos->red_root, SIZE, i, 1, j);
					j++;
				}
			}
			i++;
		}
	}
	else if (color == blue)
	{
		while (i <= SIZE && !end)
		{
			if (infos->plateau[i - 1][SIZE - 1] == blue)
			{
				j = 1;
				while (j <= SIZE && !end)
				{
					if (infos->plateau[j - 1][0] == blue)
						end = nodes_linked(infos->blue_root, i, SIZE, j, 1);
					j++;
				}
			}
			i++;
		}
	}
	return (end);
}
