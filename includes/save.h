#ifndef __SAVE_H__
#define __SAVE_H__

#include <stdio.h>
#include "hex.h"

void delete_save (void);
void make_save (int X, int Y, State color);
Infos load_save (void);
Infos cancel_coup (Infos infos);

#endif