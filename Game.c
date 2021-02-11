#include "Game_Play.h"

int main (int argc, char **argv) {

  srand(time(0));
  start();
  char* nplayer1 = info_player(1);
  char* nplayer2 = info_player_2(nplayer1);

  int choice = choose_game_settings(); 
  int dimension = board_dim(choice)+1;
  int n_boats = number_boats(dimension-1);
  game game_start_ = create_board(dimension);
  game* game_start = &game_start_;
  cell** mapa_1 = game_start->matrix_p1;
  cell** mapa_2 = game_start->matrix_p2;

  fill_board(game_start,dimension);
  print_board(dimension,mapa_1);
  printf("This will be the playing board, pick your boat placement accordingly\nPress ENTER to continue\n");

  getchar();
  printf("Each player can pick a max of %d ships, and there needs to be atleast one of each type\n",n_boats);
  printf("These are the types of boats avaiable:\n" );
  printf("1:\n         []  \n         []\n[][][X][][]\n         []\n         []\n");
  printf("\n2:\n\n[X][]\n");
  printf("\n3:\n\n[][X][]\n");
  printf("\n4:\n\n[][X][][]\n");
  printf("\n5:\n\n[][][X][][]\n");
  printf("\nThese examples show their default orientation that u can change when specifying the rotation\n\nThe X is a reference to the cell you choose in the board, all the other pieces of the ship \n\nwill be placed relatively to that one like it shows in the examples and the rotations will use that cell as the pivot\n");
  printf("\nBoth players will have access to the same ships, needing to be atleast a ship of each type  and a maximum of %d ships for each player.\n\n",n_boats);

  int* n_ships= n_ships_choice(n_boats); //arrayn em que os valores são o nº de barcos das respetivas posições


  int boat_cells = get_boat_cells(n_ships);

  set_game(mapa_1,dimension,n_ships,nplayer1);
  set_game(mapa_2,dimension,n_ships,nplayer2);

  play_game(nplayer1,nplayer2,boat_cells,mapa_1,mapa_2,dimension-1);

  free(nplayer1);
  free(nplayer2);
  free(n_ships);
  free(game_start_.matrix_p1);
  free(game_start_.matrix_p2);
  for(int i=0;i<dimension;i++){
    free(game_start_.matrix_p1[i]);
    free(game_start_.matrix_p2[i]);
  }

  return 0;
}
