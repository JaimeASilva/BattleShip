#include "Game_Structure.h"


int gen_rand(int bot,int top){
  int num = ( rand()%(top-bot+1))+bot;
  return num;
}

void start(){
  printf("          __        _______ _     ____ ___  __  __ _____   _____ ___  \n" );
  printf("          \\ \\      / / ____| |   / ___/ _ \\|  \\/  | ____| |_   _/ _ \\ \n");
  printf("           \\ \\ /\\ / /|  _| | |  | |  | | | | |\\/| |  _|     | || | | |\n");
  printf("            \\ V  V / | |___| |__| |__| |_| | |  | | |___    | || |_| |\n");
  printf("             \\_/\\_/  |_____|_____\\____\\___/|_|  |_|_____|   |_| \\___/ \n");
  printf("            ____    _  _____ _____ _     _____ ____  _   _ ___ ____  \n" );
  printf("           | __ )  / \\|_   _|_   _| |   | ____/ ___|| | | |_ _|  _ \\ \n");
  printf("           |  _ \\ / _ \\ | |   | | | |   |  _| \\___ \\| |_| || || |_) |\n");
  printf("           | |_) / ___ \\| |   | | | |___| |___ ___) |  _  || ||  __/ \n");
  printf("           |____/_/   \\_\\_|   |_| |_____|_____|____/|_| |_|___|_|    \n");

}


char* info_player (int k) { //choosing the name of the first player
  char *player_name = malloc (sizeof (char) * 100);
  printf("\nName of player %d: ",k);
  scanf("%[^\n]%*c", player_name);
  return player_name;
}

char* info_player_2(char* player1){//choosing the name of the second player and
  char* player_name_2=info_player(2);//making sure the names are different
  while (1) {
    if(strcmp(player1,player_name_2)==0){
      printf("Sorry, it seems like %s stole that from you ...\n",player1);
      player_name_2=info_player(2);
    }
    else return player_name_2;
  }
}

int choose_game_settings(){//Choosing between manual or random dimension for the
  char choice[100]={'\0'};//board
  printf("\nDo you want the board dimensions to be set randomly or mannualy?\n1-Random\n2-Manual\n" );
  scanf("%s", choice);
  while (1) {
    int num = atoi(choice);
    if ( choice[1]=='\0' && (num==1 || num==2) ){
      return num;
      break;
    }
    else {
    printf("Pick an existing option pls!\n");
    printf("\nDo you want the board and boats to be set randomly or mannualy?\n1-Random\n2-Manual\n" );
    scanf("%s", choice);
    }
  }
}

int board_dim(int choice){//getting the board's dimension
  char n[100]={'\0'};
  if(choice==2){
    printf("Choose a number between 20 and 40 to have has the size of the board!\n");
    scanf("%s", n);
    while(1){
      int num = atoi(n);
      if( n[1]=='\0' && (num<20||num>40)){
        printf("Please choose a number between the given paramatheres!\n");
        printf("Choose a number between 20 and 40 to have has the size of the board!\n");
        scanf("%s", n);
      }
      else{
        return num;
        break;
      }
    }
  }
  else{
    int num=gen_rand(20,40);
    return num;
  }
}


int number_boats(int dimension){//calculating the maximum number of boats based
  return dimension*dimension/25;//on the dimension of the board
}

int* number_ships_used(int maximum){
  int* n_ships_type = (int*)malloc(6*sizeof(int));
  int num;
  int max;
  int total=0;
  for(int i=1;i<6;i++){
    max = maximum-total-(5-i)+1;
    printf("How many ships of type %d?\nIt needs to be higher than 0 and lower than %d\n",i,max);
    scanf("%d",&num);
    while (1){
      if(num>=max || num <0){
        printf("\nThe value doesn't fit the requirements.\nPlease Choose a value between 0 and %d\n",max );
        scanf("%d",&num);
      }
      else{
        n_ships_type[i]=num;
        total+=num;
        break;
      }
    }
  }
  return n_ships_type;
}


int* number_ships_used_rand(int maximum){
  int* n_ships_type = (int*)malloc(6*sizeof(int));
  int num;
  int max;
  int total=0;
  for(int i=1;i<6;i++){
    max = maximum-total-(5-i)+1;
    num = gen_rand(1,max-1);
    n_ships_type[i]=num;
    total+=num;
  }
  return n_ships_type;
}

int* n_ships_choice(int maximum){
  int x;
  char choice[100]={'\0'};
  printf("Would you like to choose the number and type of boats or have it randomized?\n1-Manual\n2-Random\n->" );
  scanf("%s",choice);
  x = atoi(choice);
  while (1) {
    if(x==1 && choice[1]=='\0') return number_ships_used(maximum);
    else if(x==2 && choice[1]=='\0') return number_ships_used_rand(maximum);
    else {
      printf("That input is invalid\nWould you like to choose the number and type of boats or have it randomized?\n1-Manual\n2-Random\n->" );
      scanf("%s",choice);
      x = atoi(choice);
    }
  }
}

int get_boat_cells(int* arr){
  int count=0;
  for(int i=0;i<6;i++){
    switch (i) {
      case 1:
      count+=9*arr[i];
      break;
      case 2:
      count+=2*arr[i];
      break;
      case 3:
      count+=3*arr[i];
      break;
      case 4:
      count+=4*arr[i];
      break;
      case 5:
      count+=5*arr[i];
      break;
    }
  }
  return count;
}

game create_board(int n){
  game game_init;

  game_init.matrix_p1 =(cell**)malloc(n*sizeof(cell));
  game_init.matrix_p2 =(cell**)malloc(n*sizeof(cell));

  for(int i=0;i<n;i++){
    game_init.matrix_p1[i]=(cell*)malloc(n*sizeof(cell));
    game_init.matrix_p2[i]=(cell*)malloc(n*sizeof(cell));
  }

  return game_init;
}

/////////////////////////////////////////////

////////////////////////////////////////

void fill_board(game* map,int n) {
  char car1 = 'A', car2 = 'a';
  char  b;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if(j==0 && i!=0) {
	if (i <= 26) {
	  b = car1;
	  map->matrix_p1[i][j].state= b;
	  map->matrix_p2[i][j].state= b;
	  car1++;
	}
	else {
	  map->matrix_p1[i][j].state= car2;
	  map->matrix_p2[i][j].state= car2;
	  car2++;
	}
      }
      else {map->matrix_p1[i][j].state=0;
            map->matrix_p2[i][j].state=0;
      }
    }
  }
  map->matrix_p1[0][0].state='$';
  map->matrix_p2[0][0].state='$';
}

void print_board(int n, cell** map) {
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(i==0 && j!=0) {
	if (j >= 10) {
    printf("\033[1;33m");
    printf(" %d", j);
    printf("\033[0m");
	}
	else {
    printf("\033[1;33m");
	  printf("  %d", j);
    printf("\033[0m");
	}
      }
      else if (j==0 && i!=0) {
        printf("\033[1;33m");
        printf("  %c", map[i][j].state);
        printf("\033[0m");
      }
      else if (i == 0 && j == 0){
        printf("\033[0;33m");
        printf("  %c", map[i][j].state);
        printf("\033[0m");
      }
      else if (map[i][j].state==1){
          printf("\033[1;32m");
          printf(" .%d", map[i][j].state);
          printf("\033[0m");
      }
      else{
        printf("\033[1;34m");
        printf(" .%d", map[i][j].state);
        printf("\033[0m");
     }
    }
    printf("\n");
  }
}

void print_enemy_board(int n, cell** map) {
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(i==0 && j!=0) {
  if (j >= 10) {
    printf("\033[1;33m");
    printf(" %d", j);
    printf("\033[0m");
  }
  else {
    printf("\033[1;33m");
    printf("  %d", j);
    printf("\033[0m");
  }
      }
      else if (j==0 && i!=0) {
        printf("\033[1;33m");
        printf("  %c", map[i][j].state);
        printf("\033[0m");
      }
      else if (i == 0 && j == 0){
        printf("\033[0;33m");
        printf("  %c", map[i][j].state);
        printf("\033[0m");
      }
      else if (map[i][j].state!=0){
          if(map[i][j].state==1){
            printf("\033[1;34m");
            printf(" .0");
            printf("\033[0m");
          } //barco escondido
          if(map[i][j].state==2){
            printf("\033[1;32m");
            printf(" .1");
            printf("\033[0m");
          }//barco atingido
          else if(map[i][j].state==3){
            printf("\033[1;31m");
            printf(" .2");
            printf("\033[0m");
          }//tiro falhado
      }
      else{
        printf("\033[1;34m");
        printf(" .%d", map[i][j].state);
        printf("\033[0m");
      }
    }
    printf("\n");
  }
}
