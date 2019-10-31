# include <stdio.h>
# include <stdlib.h>
# include "print.h"


void print_table( agenda *array){
  int j, k;
  // output table
  for(j = 0; j <= 28; j++){
    //printf("j = %d\n",j);
    line();
    for(k = 0; k <= 7; k++){
      //printf("k = %d\n",k);
      fence();
      switch (k) {
        case 0:
          if (j == 0)
            printf(" time\\day ");
          else
            printf("%4d: %d0  ", hour(j-1), min(j-1));
          break;
        default:
          switch(j){
          case 0:
            printf("%10s", array[k-1].day);
            break;
          default:
            printf("\033[0;34m");//set printing color to be blue
            printf("%10s", array[k-1].time[j-1]);
            printf("\033[0m");//free setting
          }
      }
    } 
    fence();
    printf("\n");
  }
  line();
}

int hour(int n){
  return n/2 + 8;
}

int min(int n){
  if (n % 2 == 1)
    return 3;
  else
    return 0;
}

//feed a line of intersections between each row
void line(){
  printf("-----------------------------------------------------------------------------------------\n");
}

//feed a line to set apart columns
void fence(){
  printf("|");
}
