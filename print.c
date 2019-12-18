# include <stdio.h>
# include <stdlib.h>
# include "print.h"
# include "io.h"


void print_table( agenda *array){
  int j, k;
  // output table
  printf("Generated Schedule:\n");
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

void file_print_table(agenda *array){
  int j, k;
  // output table
  FILE * fp = fopen("output_table.txt", "w");
  fprintf(fp, "Generated Schedule:\n");
  for(j = 0; j <= 28; j++){
    //printf("j = %d\n",j);
    fprintf(fp, "-----------------------------------------------------------------------------------------\n");
    for(k = 0; k <= 7; k++){
      //printf("k = %d\n",k);
      fprintf(fp, "|");
      switch (k) {
        case 0:
          if (j == 0)
            fprintf(fp, " time\\day ");
          else
            fprintf(fp, "%4d: %d0  ", hour(j-1), min(j-1));
          break;
        default:
          switch(j){
          case 0:
            fprintf(fp, "%10s", array[k-1].day);
            break;
          default:
            fprintf(fp, "%10s", array[k-1].time[j-1]);
          }
      }
    }
    fprintf(fp, "|");
    fprintf(fp, "\n");
  }
  fprintf(fp, "-----------------------------------------------------------------------------------------\n");
  fclose(fp);
  printf("Generated output table is stored in \"output_table.txt\"\n");
}
//feed a line of intersections between each row
void line(){
  printf("-----------------------------------------------------------------------------------------\n");
}

//feed a line to set apart columns
void fence(){
  printf("|");
}

