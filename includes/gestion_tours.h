#ifndef __GESTION_TOURS_H__
#define __GESTION_TOURS_H__

#include <stdlib.h>
#include <stdbool.h>
#include "types.h"

#define SIZE 11

bool add_pion (Infos infos, int X, int Y, State color);
bool end_of_game (Infos infos, State color);

#endif