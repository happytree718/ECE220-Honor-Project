# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "print.h"
# include "io.h"


void stop_everything(int sig){
printf("\n********************************************************************************************\n");
printf("You have successfully left the program.\n");
printf("Please type \033[0;32mmake\033[0m and then type \033[0;32m./main\033[0m to restart the program\n");
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

  int m, n;
  //initial all the strings to dashes
  for(m = 0; m <= 6; m++){
    for(n = 0; n <= 27; n++){
      day[m].time[n] = "-----";
    }
  }
  int option = 0;
  mem * list;
  slot * time;
  char filename[100];
  while(option != 1 && option != 2){
    printf("Please choose the way to input data :\n");
    printf("1: stdin; 2: file input\n");
    scanf("%d", &option);
    if (option == 1){
      //list = member_input();
      //time = timeslot_input();
    }else if (option == 2){
      printf("Please enter the name of the file you want to load member data:\n");
      printf("* Make sure the file is in correct format(similar to the example below)\n");
      printf("2\nN Alex\nT 0 1300 1500\nT 2 0800 0930\nN Beta\nT 3 1530 1640\n");
      scanf("%s", filename);
      list = file_member_input(filename);
      printf("Please enter the name of the file you want to load time slot data\n:");
      scanf("%s", filename);
      time = file_timeslot_input(filename);
    }else{
      printf("Invalid choice.\n");
    }
  }




  // for (m = 0; m < a; m++){
  //   //printf("1");
  //   for (n = 0; n < b; n++){
  //     //printf("2");
  //     if (list[m].day == time[n].day){
  //       //printf("day checked\n");
  //       if (list[m].start_time <= time[n].start_time && list[m].end_time >= time[n].end_time){
  //         //printf("time checked");
  //         for(i = start_time_to_index(time[n].start_time); i <= end_time_to_index(time[n].end_time); i++ ){
  //           //printf("FOUND\n");
  //           day[list[m].day].time[i] = list[m].name;
	//         }
  //       }
  //     }
  //   }
  // }

  free(list);
  free(time);
  file_print_table(day);
  print_table(day);

  return 0;
}
