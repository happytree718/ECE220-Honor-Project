# include <stdio.h>
# include <stdlib.h>
# include <string.h>


typedef struct timetable
{
  char *day;
  int start_time;
  int end_time;
  char *time[28];
  /* from 8am to 10pm, each array represent the person for this
   * half-hour period
   */
}agenda;

typedef struct worker{
  char* name;
  int day;
  int start_time;
  int end_time;
  int availability;
}mem;

typedef struct timeslot{
  int day;
  int start_time;
  int end_time;
  int num_member;
  int filled;
}slot;

int hour(int n);
int min(int n);
int start_time_to_index(int n);
int end_time_to_index(int n);
void line();
void fence();


int main(){

  agenda day[7];    //set up an array of struct for each day
  //set up initial value for each struct
  day[1].day = "Monday";
  day[2].day = "Tuesday";
  day[3].day = "Wednesday";
  day[4].day = "Thursday";
  day[5].day = "Friday";
  day[6].day = "Saturday";
  day[0].day = "Sunday";

  int m, n, j, k;
  //initial all the strings to a blank space
  for(m = 0; m <= 6; m++){
    for(n = 0; n <= 27; n++){
      day[m].time[n] = "-----";
    }
  }

  // input for member info
  printf("Please enter the number of total members:\n");
  scanf("%d", &m);
  const int a = m;
  mem list[a];
  printf("Please input members' name and availability as instructed\n");
  for (m = 0; m < a; m++){
    printf("Name: ");
    scanf("%s", list[m].name);
    printf("What day? ('0' for Sunday ~ '6' for Sunday)\n");
    scanf("%d", &list[m].day);
    printf("Start time and end time: ");
    scanf("%d %d", &list[m].start_time, &list[m].end_time);
    list[m].availability = 1;
  }

  // input for timeslot info
  printf("Please enter the number of total timeslots:\n");
  scanf("%d", &m);
  const int b = m;
  slot time[b];
  printf("Please input time slot info below\n");
  for (m = 0; m < b; m++){
    printf("What day? ('0' for Sunday ~ '6' for Sunday)\n");
    scanf("%d", &time[m].day);
    printf("Start time and end time: \n");
    scanf("%d %d", &time[m].start_time, &time[m].end_time);
    printf("Number of members per slot: \n");
    scanf("%d", time[m].num_member);
    time[m].filled = 0;
  }

  for (m = 0; m < a; m++){
    for (n = 0; n < b; n++){
      if (list[m].day = time[n].day){
        if (list[m].start_time > time[n].start_time && list[m].end_time < time[n].end_time){
          day[list[m].day] = list[m].name;
        }
      }
    }
  }
  //testing input
  //day[1].time[3] = "James";
  //day[1].time[4] = "James";
  //day[1].time[5] = "James";
  //day[3].time[4] = "Sam";
  //day[3].time[5] = "Sam";
  //testing part end

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

int start_time_to_index(int n){
  if (n % 100 = 0)
    return 2 * (n / 100 - 8);
  else if (n % 100 <= 30)
    return 2 * (n / 100 - 8) + 1;
  else
    return 2 * (n / 100 - 8) + 2;
}

int end_time_to_index(int n){
  if (n % 100 < 30)
    return 2 * (n / 100 - 8) - 1;
  else
    return 2 * (n / 100 - 8);
}

//feed a line of intersections between each row
void line(){
  printf("-----------------------------------------------------------------------------------------\n");
}

//feed a line to set apart columns
void fence(){
  printf("|");
}
