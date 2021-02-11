#ifndef GAME_PLAY_H
#define GAME_PLAY_H

#include "Game_Boats.h"
#include "Structs.h"

int get_row(int max_bound);

int get_col(int max_bound);

int get_rot(void);

bool test_pos(int type, int row, int col, int rot, cell** map, int max_bound);

void set_game(cell** map, int dimension,int* arr,char* p_name);

char* coin_toss(char* player1, char* player2);

int shoot(cell** map, char* player,int dimension);

void play_game(char* nplayer1,char* nplayer2, int boat_cells, cell** mapa1, cell** mapa2, int dimension);

#endif
