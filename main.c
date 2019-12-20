# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "print.h"
# include "io.h"


void stop_everything(int sig){
printf("\n********************************************************************************************\n");
printf("You have successfully left the program.\n");
printf("Please type \033[0;32mmake\033[0m and then type \033[0;32m./honor\033[0m to restart the program\n");
printf("See you later!\n");
printf("********************************************************************************************\n");
exit(1);
}

agenda * CreateTable(){
  agenda* day = malloc(7 * sizeof(agenda));
  //set up initial value for each struct
  int m, n;
  //initial all the strings to dashes
  for(m = 0; m <= 6; m++){
    //day[m].time = (char**)malloc(28*sizeof(char*));
    for(n = 0; n <= 27; n++){
      day[m].time[n] = (char*)malloc(10*sizeof(char));
      strcpy(day[m].time[n], "-----");
    }
  }
  strcpy(day[1].day, "Monday");
  strcpy(day[2].day, "Tuesday");
  strcpy(day[3].day, "Wednesday");
  strcpy(day[4].day, "Thursday");
  strcpy(day[5].day, "Friday");
  strcpy(day[6].day, "Saturday");
  strcpy(day[0].day, "Sunday");
  return day;
}

void destroy_table(agenda * day){
  int m, n;
  for(m = 0; m <= 6; m++){
    for(n = 0; n <= 27; n++){
      free(day[m].time[n]);
    }
  }
  free(day);
  printf("Clear generated table...\n");
  return;
}

int main(){
  signal(SIGINT, stop_everything);
  agenda * day = CreateTable();
  //set up an array of struct for each day

  int option = 0, flag = 0;
  mem * list;
  slot * time;
  char filename[30];
  while(option != 1 && option != 2){
    printf("You want to:\n");
    printf("1: generate schedule; 2: find common meeting time\n");
    scanf("%d", &option);
    if (option == 1){
      option = 0;
      while(option != 1 && option != 2){
        printf("Please choose the way to input data :\n");
        printf("1: stdin; 2: file input\n");
        scanf("%d", &option);
        if (option == 1){
          time = timeslot_input();
          list = member_input();
        }else if (option == 2){
          printf("WELCOME TO THE SCHEDULE GENERATOR!");
          printf("Please make sure the file is in correct format(similar to the example below)\n");
          printf("2\nN Alex\nT 0 1300 1500\nT 2 0800 0930\nN Beta\nT 3 1530 1640\n");
          printf("3\n0 1200 1400 1\n2 0824 1322 3\n5 0930 1030 1\n");
          printf("Please enter the name of the file you want to load time slot data\n:");
          scanf("%s", filename);
          time = file_timeslot_input(filename);
          printf("Please enter the name of the file you want to load member data:\n");
          scanf("%s", filename);
          list = file_member_input(filename);
        }else{
          printf("Invalid choice.\n");
        }
      }
      while (1){
        printf("\nEnter the operation you want to conduct:\n");
        printf("0: Halt the program;\n1: Exhibit loaded input;\n2: Generate Schedule(stored in \"output_table.txt\");\n3: Print generated table;\n");
        scanf("%d", &option);
        switch(option){
          case 0:
            destroy_mem_list(list);
            destroy_slot_list(time);
            destroy_table(day);
            printf("\nThe program ends.Thanks for using!\n\n");
            return 0;
            break;
          case 1:
            printf("Summarize input info:\n");
            print_mem_list(list);
            print_slot_list(time);
            break;
          case 2:
            find_match_member(time, list);
            int nth = 0;
            if (check_possible_schedule(time) && GenerateSchedule(time, &nth, list)){
            printf("Generating schedule...\n");
            //if (GenerateSchedule(time, &nth, list))
            assign_table(day, time, list);
            file_print_table(day);
            file_print_readfile(time, list);
            flag = 1;
            }else{
              printf("Sorry, it is impossible to generate the schedule based on the given information.\n");
            }
            break;
          case 3:
            if(flag == 1)
              print_table(day);
            else
              printf("Please generate table first.\n");
            break;
          default:
            printf("Invalid choice.\n");
            break;
        }
      }
    }else if(option == 2){
      option = 0;
      while(option != 1 && option != 2){
        printf("Please choose the way to input data :\n");
        printf("1: stdin; 2: file input\n");
        scanf("%d", &option);
        if (option == 1){
          list = member_input();
        }else if(option == 2){
          printf("Please enter the name of the file you want to load member data:\n");
          scanf("%s", filename);
          list = file_member_input(filename);
        }else{
          printf("Invalid choice.\n");
        }
      }
      find_common_time(day,list);
      file_print_table(day);
      while (1){
        printf("\nEnter the operation you want to conduct:\n");
        printf("0: Halt the program;\n1: Exhibit loaded input;\n2: Print all common time table;\n");
        scanf("%d", &option);
        switch(option){
          case 0:
            destroy_mem_list(list);
            destroy_table(day);
            printf("\nThe program ends.Thanks for using!\n\n");
            return 0;
            break;
          case 1:
            printf("Summarize input info:\n");
            print_mem_list(list);
            break;
          case 2:
            print_table(day);
            break;
          default:
            printf("Invalid choice.\n");
            break;
        }
      }
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
  return 0;
}
