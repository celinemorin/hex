#ifndef __SAVE_H__
#define __SAVE_H__

#include <stdio.h>
#include "hex.h"

void delete_save (void);
void make_save (int X, int Y, State color);
void load_save (Board plateau);
void cancel_coup (Board plateau);

#endif