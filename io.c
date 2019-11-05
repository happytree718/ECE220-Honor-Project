# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "print.h"
# include "io.h"


// mem * member_input(){
//   // input for member info
//   int m;
//   printf("Please enter the number of total members:\n");
//   scanf("%d", &m);
//   const int a = m;
//   mem * list = (mem *)malloc(a * sizeof(mem));
//   printf("Please input members' name and availability as instructed\n");
//   for (m = 0; m < a; m++){
//     (list + m)->name = (char*) malloc(10 * sizeof(char));
//     printf("Name: \n");
//     scanf("%s", (list+m)->name);
//     printf("What day? ('0' for Sunday ~ '6' for Sunday)\n");
//     scanf("%d", &(list+m)->day);
//     printf("Start time and end time: \n");
//     scanf("%d %d", &(list+m)->start_time, &(list+m)->end_time);
//     (list+m)->availability = 1;
//   }
//   return list;
// }
//
// slot * timeslot_input(){
//   // input for timeslot info
//   int m;
//   printf("Please enter the number of total timeslots:\n");
//   scanf("%d", &m);
//   const int b = m;
//   slot * time = (slot *) malloc (b * sizeof(slot));
//   printf("Please input time slot info below\n");
//   for (m = 0; m < b; m++){
//     printf("What day? ('0' for Sunday ~ '6' for Sunday)\n");
//     scanf("%d", &time[m].day);
//     printf("Start time and end time: \n");
//     scanf("%d %d", &time[m].start_time, &time[m].end_time);
//     printf("Number of members per slot: \n");
//     scanf("%d", &time[m].num_member);
//     (time + m)->filled = 0;
//   }
//   return time;
// }


mem * file_member_input(char* file){
  FILE * fp = fopen(file, "r");
  period * temp;
  char firstChar;
  int size, i;
  period * slot;
  fscanf(fp, "%d\n", &size);
  printf("line 57 %d\n", size);

  mem * member = (mem *) malloc(size * sizeof(mem));
  firstChar = fgetc(fp);
  printf("line 61 %c\n", firstChar);

  for (i = 0; i < size; i++){
    fgets((member+i)->name, 10, fp);
    printf("line 65 %s\n", (member+i)->name);
    (member+i)->time = NULL;
    (member+i)->availability = 1;
    fscanf(fp, "%c ", &firstChar);
    printf("line 69 %c\n", firstChar);
    while (firstChar == 'T'){
      slot = (period *) malloc(sizeof(period));
      fscanf(fp, "%d %d %d\n", &(slot->day), &(slot->start_time), &(slot->end_time));
      printf("line 73 %d %d %d\n", (slot->day), (slot->start_time), (slot->end_time));
      temp = (member+i)->time;
      (member+i)->time = slot;
      slot->next = temp;
      fscanf(fp, "%c ", &firstChar);
      printf("line 78 %c\n", firstChar);
      if (feof(fp)) break;
    }
  }
  fclose(fp);
  return member;
}

slot * file_timeslot_input(char* file){
  FILE * fp = fopen(file, "r");
  int i, size;
  fscanf(fp, "%d\n", &size);
  slot * slotList = (slot *) malloc(size * sizeof(slot));
  for (i = 0; i < size; i++){
    fscanf(fp, "%d %d %d %d\n", &((slotList+i)->time->day), &((slotList+i)->time->start_time), &((slotList+i)->time->end_time), &((slotList+i)->num_member));
    (slotList+i)->filled = 0;
  }
  fclose(fp);
  return slotList;
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
