#include "Game_Boats.h"

boat templates[5] = {
  { BOAT_T,
    {   {'0','0','0','0','1'},
   	{'0','0','0','0','1'},
   	{'1','1','1','1','1'},
        {'0','0','0','0','1'},
   	{'0','0','0','0','1'}
   }
  ,9
  },
  { BOAT_2,
        {{'0','0','0','0','0'},
	 {'0','0','0','0','0'},
	 {'0','0','1','1','0'},
	 {'0','0','0','0','0'},
	 {'0','0','0','0','0'}
       },
    2},
  { BOAT_3,
        {{'0','0','0','0','0'},
         {'0','0','0','0','0'},
	 {'0','1','1','1','0'},
	 {'0','0','0','0','0'},
	 {'0','0','0','0','0'}
       },
    3},
  { BOAT_4,
        {{'0','0','0','0','0'},
	 {'0','0','0','0','0'},
	 {'0','1','1','1','1'},
	 {'0','0','0','0','0'},
         {'0','0','0','0','0'}
       },
    4},
  { BOAT_5,
        {{'0','0','0','0','0'},
         {'0','0','0','0','0'},
	 {'1','1','1','1','1'},
	 {'0','0','0','0','0'},
	 {'0','0','0','0','0'}
        },
  5}
};


boat boat_rotation (boat t, int rot) {
  while (rot > 0) {
    boat B = t;
    for (int i=0; i<5; i++) {
      for (int j=0; j<5; j++) {
	t.bitmap[4-j][i] = B.bitmap[i][j];
      }
    }
    rot-=90;
  }
  return t;
}

void place_boat(boat boat, cell** map, int row, int col){
  map[row][col].boat=&boat;
  map[row][col].bit_pos[0]=2;
  map[row][col].bit_pos[1]=2;
  for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
     if(map[row][col].boat->bitmap[i][j]=='1'){
       map[row-2+i][col-2+j].state=1;
       if(!(i==2 && j==2)){
         map[row-2+i][col-2+j].boat=map[row][col].boat;
         map[row-2+i][col-2+j].bit_pos[0]=i;
         map[row-2+i][col-2+j].bit_pos[1]=j;
       }
     }
    }
  }
}


void fill_boats(int* arr, int max_bound,cell** map,char* p_name){
  int row;
  int col;
  int rot;
  printf("It's your turn to choose your ships positioning %s\n",p_name);
  for(int i=1;i<6;i++){
    for(int j=1;j<=arr[i];j++){
        while(1){
          printf("\nShip number %d of type %d",j,i );
          row = get_row(max_bound);
          col=get_col(max_bound);
          rot=get_rot();
          if(test_pos(i,row,col,rot,map,max_bound)){
            boat boat;
            switch (i) {
              case 1:
              boat = templates[BOAT_T];
              break;
              case 2:
              boat = templates[BOAT_2];
              break;
              case 3:
              boat = templates[BOAT_3];
              break;
              case 4:
              boat = templates[BOAT_4];
              break;
              case 5:
              boat = templates[BOAT_5];
              break;
            }
            boat=boat_rotation(boat,rot);
            place_boat(boat,map,row,col);
            print_board(max_bound,map);
            printf("O barco foi colocado\n");
            break;
          }
          else{
            printf("This ship can't be placed in that position with the given coordinates and/or rotation, please try again.\n");
            row = get_row(max_bound);
            col=get_col(max_bound);
            rot=get_rot();
          }
        }
    }
  }
  printf("This is the board of %s:\n",p_name);
  print_board(max_bound,map);
}


void fill_boats_rand(int* arr, int max_bound, cell** map,char* p_name){
  int row;
  int col;
  int rot;
  int rot_pool[4]={0,90,180,270};
  for(int i=1;i<6;i++){
    for(int j=1;j<=arr[i];j++){
      while(1){
        row=gen_rand(1,max_bound-1);
        col=gen_rand(1,max_bound-1);
        rot=rot_pool[gen_rand(0,3)];
        if(test_pos(i,row,col,rot,map,max_bound)){
          boat boat;
          switch (i) {
            case 1:
            boat = templates[BOAT_T];
            break;
            case 2:
            boat = templates[BOAT_2];
            break;
            case 3:
            boat = templates[BOAT_3];
            break;
            case 4:
            boat = templates[BOAT_4];
            break;
            case 5:
            boat = templates[BOAT_5];
            break;
          }
          boat=boat_rotation(boat,rot);
          place_boat(boat,map,row,col);
          break;
        }
        else{
          row=gen_rand(1,max_bound-1);
          col=gen_rand(1,max_bound-1);
          rot=rot_pool[gen_rand(0,3)];
        }
      }
    }
  }
  printf("This is the board of %s:\n",p_name);
  print_board(max_bound,map);
}

bool verify_shot(int row,int col,cell** map){
  int x = map[row][col].bit_pos[0];
  int y = map[row][col].bit_pos[1];
  if(map[row][col].state == 1){
    map[row][col].boat->bitmap[x][y]='2';
    map[row][col].state=2;
    map[row][col].boat->size--;
    return true;
  }
  else if(map[row][col].state == 0){
    map[row][col].state=3;
    return false;
  }
  else return false;
}
