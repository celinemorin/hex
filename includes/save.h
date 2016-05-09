#ifndef __SAVE_H__
#define __SAVE_H__

#include <stdio.h>
#include <string.h>
#include "types.h"

void make_save (int X, int Y, State color);
Infos load_save (void);
Infos cancel_coup (Infos infos);
int *historique (int nb);

#endif