#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum {false, true} bool;
typedef enum {BOAT_T,BOAT_2,BOAT_3,BOAT_4,BOAT_5} BOAT_TYPE;

typedef struct {
  BOAT_TYPE type;
  char bitmap[5][5];
  char size;
}boat;

typedef struct{
  boat* boat;
  char state;
  int bit_pos[2];
}cell;

typedef struct{
 cell** matrix_p1;
 cell** matrix_p2;
}game;




#endif
