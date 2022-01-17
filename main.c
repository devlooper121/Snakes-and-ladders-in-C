#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<unistd.h>
// for win count;
int winCount = 1;
int noOfPlayers;
int lStart[] = {2,8,20,32,41,74,85};
int lEnd[] = {23,34,77,68,84,99,95};
int sStart[] = {29,38,47,53,62,82,92,97};
int sEnd[] = {9,15,5,33,37,54,70,25};

char goti[] = "abcdefghijklmnopqrstuvwxyz";
void draw(int player, int players[]){
    int x = 100;
    int y = players[player];
    players[player]++;
    for(int i = 0; i <= 21; i++){
        for(int j = 0; j <= 22; j++){
            char temp[] = "";
            if(i == 0 || j == 0 || j == 22 || i == 21){
                printf("# ##");
            }else if(j%2 != 0 && i%2 != 0){
                printf("|");
            }else if(i%2 == 0){
                printf("- --");
            }
            else{
                for(int p = 0; p < noOfPlayers; p++){
                    if(players[p] == x){
                        temp[p] = goti[p];
                    }else{
                        temp[p] = ' ';
                    }
                }
                if(x == 100 && i == 1 && j == 2){
                    printf("%-7s","win!");
                    x--;
                }
                else
                    printf("%-.2d %.4s",x--,temp);
            }
        }

        printf("\n");
    }

}
void drawme(int player, int next,int players[]){

    while(players[player] < next){
        sleep(1);
        system("cls");
        draw(player,players);

    }
}

int rollDice(void){
  srand(time(0));
  int randomNumber = (rand()%6)+1;
  return randomNumber;
}

void game(int players[]){
    for (int i = 0; i < noOfPlayers; i++){

      // for printing score board
      for (int i = 0; i < noOfPlayers; i++){
        printf("Player %d is at point : %d.\n", i+1, players[i]);
      }

      if(players[i] != 100){
        printf("\nIts Player %d term.\n\n", i+1);
      }

      if (players[i] == 0){
      // players get three chance until 1
        for(int j = 3; j > 0 ; j--){
          int temp;
          printf("Player %d press Enter\n", i+1);
          getchar();
          int point = rollDice();
          printf("player %d get %d.\n",i+1, point);
          if(point == 1){

            drawme(i,1, players);
            break;
          }else{
            printf("Player %d have %d chance left\n\n", i+1, j-1);
          }
        }
        // printf("Hello welcome to Snake and ladder game !\n");
      }
      else if(players[i] > 0 && players[i] < 100){
        printf("\nPlayer %d press Enter\n", i+1);
        getchar();
        int points = rollDice();
        printf("player %d get %d.\n",i+1, points);
        if(players[i]+points > 100){
          printf("\nPlayer %d get invalid number.\n",i);
          continue;
        }
        int prev = players[i];
        int point = prev + points;
        drawme(i,point, players);
        // ladders
        for(int k = 0; k < 7; k++){
            if(point == lStart[k]){
                //players[i] = lEnd[k];
                printf("Wow Player %d get a ladder %d to %d\n.", i+1,lStart[k],lEnd[k]);
                sleep(2);
                drawme(i,lEnd[k],players);
            }
        }
        for(int k = 0; k < 8; k++){
            if(point == sStart[k]){
                players[i] = sEnd[k]-1;
                printf("Oh!! Player %d bitten by a snake from %d to %d\n.", i+1,sStart[k],sEnd[k]);
                sleep(2);
                draw(i,players);
            }
        }

        if(point == 100){
          printf("\nPlayer %d won and get RANK '%d'\n", i+1, winCount++);
          break;
        }
      }

    }
}

int main(void) {

  printf("Hello welcome to Snake and ladder game !\n");
  printf("type How many Player are there ? ");
  scanf("%d", &noOfPlayers);
  getchar();
  int players[noOfPlayers];
  // code below make variable size array all zero initialization;
  for(int i = 0; i < noOfPlayers; i++){
      players[i] = 0;
  }

  while(winCount < noOfPlayers){

    game(players);

  }

  return 0;
}
