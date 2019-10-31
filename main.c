# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "print.h"
# include "io.h"


mem * member_input(){
  // input for member info
  printf("Please enter the number of total members:\n");
  scanf("%d", &m);
  const int a = m;
  mem * list = (mem *)malloc(a, sizeof(mem));
  printf("Please input members' name and availability as instructed\n");
  for (m = 0; m < a; m++){
    (list + m)->name = (char*) malloc(10 * sizeof(char));
    printf("Name: \n");
    scanf("%s", (list+m)->name);
    printf("What day? ('0' for Sunday ~ '6' for Sunday)\n");
    scanf("%d", &(list+m)->day);
    printf("Start time and end time: \n");
    scanf("%d %d", &(list+m)->start_time, &(list+m)->end_time);
    (list+m)->availability = 1;
  }
  return list;
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
