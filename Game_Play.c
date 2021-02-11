#include "Game_Play.h"


int get_row(int max_bound){
  int row_num;
  if(max_bound >26) max_bound=max_bound-26+97;
  else max_bound+=65;

  char row[100]={'\0'};
  printf("\nPlease select the row (using the figure above as reference):");
  scanf("%s",row);
  while (1) {
    row_num = (int)row[0];
    if(row[1]!='\0' || row_num>=max_bound){
        printf("\nThat row is out of bounds, please select a valid value");
        printf("\nPlease select the row (using the figure above as reference):");
        scanf("%s",row);
    }
    else if(97<=row_num && row_num<=122){
      row_num -= 70;
      break;
    }
    else if (65<=row_num && row_num<=90){
      row_num -= 64;
      break;
    }
    else{
      printf("That row is out of bounds, please select a valid value\n");
      printf("\nPlease select the row (using the figure above as reference):");
      scanf("%s",row);
    }
  }
  return row_num;
}


int get_col(int max_bound){
  int col_num;
  char col[100]={'\0'};
  printf("\nPlease select the collumn (using the figure above as reference):");
  scanf("%s",col);
  while (1) {
    col_num=atoi(col);
    if(col[2]!='\0'){
        printf("\nThat collumn is out of bounds, please select a valid value");
        printf("\nPlease select the collumn (using the figure above as reference):");
        scanf("%s",col);
    }
    else if(1>col_num || col_num>=max_bound){
      printf("\nThat collumn is out of bounds, please select a valid value");
      printf("\nPlease select the collumn (using the figure above as reference):");
      scanf("%s",col);
    }
    else{
      break;
    }
  }
  return col_num;
}



int get_rot(void){
  int rot_num;
  char rot[100]={'\0'};
  printf("\nPlease select the rotation as 0, 90, 180 or 270 (being 0 the same as the examples above):");
  scanf("%s",rot);
  while (1) {
    rot_num=atoi(rot);
    if( !(48<=rot[0] && rot[0]<=57) || rot[3] != '\0' || (rot_num==0 && rot[1] != '\0') || (rot_num==90 && rot[2] != '\0')) {
        printf("\nThat rotation is invalid, please select a valid value");
        printf("\nPlease select the rotation as 0, 90, 180 or 270 (being 0 the same as the examples above):");
        scanf("%s",rot);
    }
    else if(rot_num!= 0 && rot_num!= 90 && rot_num!= 180 && rot_num!=270 && rot_num!=360 ){
      printf("\nThat rotation is invalid, please select a valid value");
      printf("\nPlease select the rotation as 0, 90, 180 or 270 (being 0 the same as the examples above):");
      scanf("%s",rot);
    }
    else{
      break;
    }
  }
  if(rot_num==360)rot_num=0;
  return rot_num;
}

bool test_pos(int type, int row, int col, int rot, cell** map, int max_bound){ ///
  switch (type) {
    case 1:;
      int limit_l;
      limit_l=col-2;
      int limit_r;
      limit_r=col+2;
      int limit_up;
      limit_up=row-2;
      int limit_down;
      limit_down=row+2;
      if(max_bound<=limit_r || max_bound<=limit_down || limit_l<1 || limit_up<1)return false;
      if(rot==0){

        for(int i=0;i<5;i++){
          if(map[row][limit_l+i].state != 0) return false;
          if(map[limit_up+i][limit_r].state != 0) return false;
        }
      }
      else if(rot==90){
        for(int i=0;i<5;i++){
          if(map[limit_up][limit_l+i].state != 0) return false;
          if(map[limit_up+i][col].state != 0) return false;
        }
      }
      else if(rot==180){
        for(int i=0;i<5;i++){
          if(map[row][limit_l+i].state != 0) return false;
          if(map[limit_up+i][limit_l].state != 0) return false;
        }
      }
      else if(rot==270){
        for(int i=0;i<5;i++){
          if(map[limit_up+i][col].state != 0) return false;
          if(map[limit_down][limit_l+i].state != 0) return false;
        }
      }
      break;
    case 2:
      if(rot == 0){
        if(col +1 >= max_bound) return false;
        for(int i=0;i<2;i++){
          if(map[row][col+i].state!=0) return false;
        }
      }
      else if(rot == 90){
        if(row-1 < 1) return false;
        for(int i=0;i<2;i++){
          if(map[row-i][col].state!=0) return false;
        }
      }
      else if(rot == 180){
        if(col-1 < 1) return false;
        for(int i=0;i<2;i++){
          if(map[row][col-i].state!=0) return false;
        }
      }
      else if(rot == 270){
        if(row+1 >= max_bound) return false;
        for(int i=0;i<2;i++){
          if(map[row+i][col].state!=0) return false;
        }
      }
      break;
    case 3:
    if(rot == 0 || rot ==180){
      if(col +1 >= max_bound || col -1 < 1) return false;
      for(int i=0;i<3;i++){
        if(map[row][col-1+i].state!=0) return false;
      }
    }
    else if(rot == 90 || rot==270){
      if(row-1 < 1 || row+1 >= max_bound) return false;
      for(int i=0;i<3;i++){
        if(map[row-1+i][col].state!=0) return false;
      }
    }
      break;
    case 4:
    if(rot == 0){
      if(col +2 >= max_bound || col -1 <1) return false;
      for(int i=0;i<4;i++){
        if(map[row][col-1+i].state!=0) return false;
      }
    }
    else if(rot == 90){
      if(row-2 < 1 || row+1 >= max_bound) return false;
      for(int i=0;i<4;i++){
        if(map[row+1-i][col].state!=0) return false;
      }
    }
    else if(rot == 180){
      if(col-2 < 1 || col+1 >= max_bound) return false;
      for(int i=0;i<4;i++){
        if(map[row][col+1-i].state!=0) return false;
      }
    }
    else if(rot == 270){
      if(row+2 >= max_bound || row-1 < 1) return false;
      for(int i=0;i<4;i++){
        if(map[row-1+i][col].state!=0) return false;
      }
    }
      break;
    case 5:
    if(rot == 0 || rot == 180){
      if(col +2 >= max_bound || col-2<1) return false;
      for(int i=0;i<5;i++){
        if(map[row][col-2+i].state!=0) return false;
      }
    }
    else if(rot == 90 || rot == 270){
      if(row +2 >= max_bound || row-2<1) return false;
      for(int i=0;i<5;i++){
        if(map[row-2+i][col].state!=0) return false;
      }
    }
      break;
  }
  return true;
}

void set_game(cell** map, int dimension,int* arr,char* p_name){
  int x;
  char choice[100]={'\0'};
  printf("%s would you like to have your boat's placement choosen\n1-Manually\n2-Randomized\n->",p_name);
  scanf("%s",choice);
  x = atoi(choice);
  while (1) {
    if(x==1 && choice[1]=='\0'){
      fill_boats(arr,dimension,map,p_name);
      break;
    }
    else if(x==2 && choice[1]=='\0'){
      fill_boats_rand(arr,dimension,map,p_name);
      break;
    }
    else {
      printf("That input is invalid\n%s would you like to have you boat's placement choosen\n1-Manually\nRandomized\n->",p_name);
      scanf("%s",choice);
      x = atoi(choice);
    }
  }
}

///////////////
char* coin_toss(char* player1, char* player2){
  printf("Ok, let's have a coin toss to see who goes first!\n");
  char choice[100]={'\0'};
  int x;
  if(gen_rand(1,2)==1){
    printf("%s you choose, 1 for Heads and 2 for tails\nWhat will it be?\n->",player1 );
    scanf("%s",choice);
    x=atoi(choice);
    int rand = gen_rand(1,2);
    while (1) {
      if(choice[1]=='\0' && rand==x ) return player1;
      else if (choice[1]=='\0' && rand!=x && x!=0) return player2;
      else{
        printf("Pls type either 1 or 2!\n%s you choose, 1 for Heads and 2 for tails\nWhat will it be?\n->",player1 );
        scanf("%s",choice);
        x=atoi(choice);
      }
    }
  }
  else{
    printf("%s you choose, 1 for Heads and 2 for tails\nWhat will it be?\n->",player2 );
    scanf("%s",choice);
    x=atoi(choice);
    int rand = gen_rand(1,2);
    while (1) {
      if(choice[1]=='\0' && rand==x) return player2;
      else if (choice[1]=='\0' && rand!=x && x!=0) return player1;
      else{
        printf("Pls type either 1 or 2!\n%s you choose, 1 for Heads and 2 for tails\nWhat will it be?\n->",player2 );
        scanf("%s",choice);
        x=atoi(choice);
      }
    }
  }
}


int shoot(cell** map, char* player,int dimension){
  print_enemy_board(dimension,map);
  printf("\nIts %s's turn\n", player);
  int row=get_row(dimension);
  int col=get_col(dimension);
  if(verify_shot(row,col,map)){
    printf("\nNice one! That was a hit!\n\n");
    if(map[row][col].boat->size==0) printf("That boat just got fully destroyed\n");
    return 1;
  }
  else{
    printf("\nUff ... that was a miss\n\n");
    return 0;
  }
}



void play_game(char* nplayer1,char* nplayer2, int boat_cells, cell** mapa1, cell** mapa2, int dimension){
  int boat_cells_2 = boat_cells;
  char goes_first[100];
  int order;
  int flag;
  strcpy(goes_first,coin_toss(nplayer1,nplayer2));
  if((strcmp(goes_first,nplayer1))==0) order=1;
  else order=2;
  printf("Alright %s, you won the coin toss!\n", goes_first);
  while(boat_cells>0 && boat_cells_2>0 ){
    if(order==1){
      boat_cells_2-=shoot(mapa2,nplayer1,dimension);
      flag=1;
      if(boat_cells_2==0) break;
      boat_cells-=shoot(mapa1,nplayer2,dimension);
      flag=2;
    }
    else if(order==2){
      boat_cells-=shoot(mapa1,nplayer2,dimension);
      flag=2;
      if(boat_cells==0) break;
      boat_cells_2-=shoot(mapa2,nplayer1,dimension);
      flag=1;
    }
  }
  if(flag==1) printf("Congratulation %s you won!!!\n",nplayer1 );
  else if(flag ==2)printf("Congratulation %s you won!!!\n",nplayer2 );
}
