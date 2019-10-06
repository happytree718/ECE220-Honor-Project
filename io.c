# include <stdio.h>
# include <string.h>


struct agenda
{
  char *day;
  int start_time;
  int end_time;
  char *time[28];
  /* from 8am to 10pm, each array represent the person for this
   * half-hour period
   */
};
int hour(int n);
int min(int n);
void line();
void fence();


int main(){

  struct agenda day[7];    //set up an array of struct for each day
  //set up initial value for each struct
  day[0].day = "Monday";
  day[1].day = "Tuesday";
  day[2].day = "Wednesday";
  day[3].day = "Thursday";
  day[4].day = "Friday";
  day[5].day = "Saturday";
  day[6].day = "Sunday";

  int m, n, j, k;
  //initial all the strings to a blank space
  for(m = 0; m <= 6; m++){
    for(n = 0; n <= 27; n++){
      day[m].time[n] = "-----";
    }
  }


//testing input
  day[1].time[3] = "James";
  day[1].time[4] = "James";
  day[1].time[5] = "James";
  day[3].time[4] = "Sam";
  day[3].time[5] = "Sam";
//testing part end

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
            printf("%10s", day[k-1].day);
            break;
          default:
	    printf("\033[0;34m");//set printing color to be blue
            printf("%10s", day[k-1].time[j-1]);
	    printf("\033[0m");//free setting
        }
      }
    }
    fence();
    printf("\n");
  }
  line();
  return 0;
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
