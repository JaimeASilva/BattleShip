#ifndef GAME_STRUCTUE_H
#define GAME_STRUCTUE_H

#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include<stdlib.h>

#include"Game_Play.h"
#include "Structs.h"



//functions

int gen_rand(int bot,int top);// get random value

void start(void);

char* info_player (int k);

char* info_player_2(char* player1);

int choose_game_settings();

int board_dim(int choice);

int number_boats(int dimension);

int* number_ships_used(int maximum);

int* number_ships_used_rand(int maximum);

int* n_ships_choice(int maximum);

int get_boat_cells(int* arr);

game create_board(int n);

void fill_board(game* map,int n);

void print_board(int n, cell** map);

void print_enemy_board(int n, cell** map);

#endif
