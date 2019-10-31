# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "print.h"
# include "io.h"


void stop_everything(int sig){
printf("\n********************************************************************************************\n");
printf("You have successfully left the program.\n");
printf("Please type \033[0;32mmake\033[0m and then type \033[0;32m./io\033[0m to restart the program\n");
printf("See you later!\n");
printf("********************************************************************************************\n");
exit(1);
}

int main(){
  signal(SIGINT, stop_everything);
  
  //set up an array of struct for each day
  agenda day[7];    
  //set up initial value for each struct
  day[1].day = "Monday";
  day[2].day = "Tuesday";
  day[3].day = "Wednesday";
  day[4].day = "Thursday";
  day[5].day = "Friday";
  day[6].day = "Saturday";
  day[0].day = "Sunday";

  int m, n, i;
  //initial all the strings to dashes
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
    printf("Name: \n");
    scanf("%s", list[m].name);
    printf("What day? ('0' for Sunday ~ '6' for Sunday)\n");
    scanf("%d", &list[m].day);
    printf("Start time and end time: \n");
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
    scanf("%d", &time[m].num_member);
    time[m].filled = 0;
  }

  for (m = 0; m < a; m++){
    //printf("1");
    for (n = 0; n < b; n++){
      //printf("2");
      if (list[m].day == time[n].day){
        //printf("day checked\n");
        if (list[m].start_time <= time[n].start_time && list[m].end_time >= time[n].end_time){
          //printf("time checked");
          for(i = start_time_to_index(time[n].start_time); i <= end_time_to_index(time[n].end_time); i++ ){
            //printf("FOUND\n");
            day[list[m].day].time[i] = list[m].name;
	        }
        }
      }
    }
  }

  print_table(day);

  return 0;
}

int start_time_to_index(int n){
  if (n % 100 == 0)
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
