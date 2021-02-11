#ifndef GAME_BOATS_H
#define GAME_BOATS_H

#include "Game_Structure.h"
#include "Structs.h"

boat boat_rotation (boat t, int rot);

void place_boat(boat boat, cell** map, int row, int col);

void fill_boats(int* arr, int max_bound,cell** map,char* p_name);

void fill_boats_rand(int* arr, int maximum, cell** map,char* p_name);

bool verify_shot(int row,int col,cell** map);


#endif
