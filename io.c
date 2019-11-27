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

int mem_list_size, slot_list_size;

/*
 * This function reads members' availability from file, 
 * Returns the pointer to an array of mem struct
 */
mem * file_member_input(char* file){
  FILE * fp = fopen(file, "r");
  printf("Loading %s ...\n", file);
  period * temp;
  char firstChar;
  int i;
  period * slot;
  fscanf(fp, "%d\n", &mem_list_size);
  //printf("line 57 %d\n", size);
  mem * member = (mem *) malloc(mem_list_size * sizeof(mem));
  fscanf(fp, "%c ", &firstChar);
  //printf("line 61 %c\n", firstChar);

  for (i = 0; i < mem_list_size; i++){
    fscanf(fp, "%s\n", (member+i)->name);
    //printf("line 65 %s\n", (member+i)->name);
    (member+i)->time = NULL;
    (member+i)->availability = 1;
    (member+i)->index = i;
    fscanf(fp, "%c ", &firstChar);
    //printf("line 69 %c\n", firstChar);
    while (firstChar == 'T'){
      slot = (period *) malloc(sizeof(period));
      fscanf(fp, "%d %d %d\n", &(slot->day), &(slot->start_time), &(slot->end_time));
      //printf("line 73 %d %d %d\n", (slot->day), (slot->start_time), (slot->end_time));
      temp = (member+i)->time;
      (member+i)->time = slot;
      slot->next = temp;
      fscanf(fp, "%c ", &firstChar);
      //printf("line 78 %c\n", firstChar);
      if (feof(fp)) break;
    }
  }
  printf("Loading complete.\n");
  fclose(fp);
  return member;
}


/*
 * This function reads time slots from file, 
 * Returns the pointer to an array of slots
 */
slot * file_timeslot_input(char* file){
  //printf("In function\n");
  FILE * fp = fopen(file, "r");
  printf("Loading %s ...\n", file);
  //printf("IN file\n");
  int i;
  //period * timeslot;
  fscanf(fp, "%d\n", &slot_list_size);
  //printf("Line92 %d\n",size);
  slot * slotList = (slot *) malloc(slot_list_size * sizeof(slot));
  for(i = 0;i<slot_list_size;i++){
    (slotList+i) -> time = malloc(sizeof(period));
  }
  for (i = 0; i < slot_list_size; i++){
    //printf("IN loop %d\n", i);
    //timeslot = (period *) malloc(sizeof(period));
    //fscanf(fp, "%d %d %d %d\n", &(timeslot->day), &(timeslot->start_time), &(timeslot->end_time), &((slotList+i)->num_member));
    fscanf(fp, "%d %d %d %d\n", &(((slotList+i)->time)->day), &(((slotList+i)->time)->start_time),
    &(((slotList+i)->time)->end_time), &((slotList+i)->num_member));
    //(slotList+i)->time = timeslot;
    //printf("%d %d %d %d\n", ((slotList+i)->time->day), ((slotList+i)->time->start_time),
    //((slotList+i)->time->end_time), ((slotList+i)->num_member));
    (slotList+i)->filled = 0;
  }
  printf("Loading complete.\n");
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

/*
 * This function frees all allocated space in the mem struct array
 */
 void destroy_mem_list(mem * ptr){
  int i;
  period * curr, * tmp;
  for (i = mem_list_size - 1; i >= 0; i--){
    curr = (ptr + i)->time;
    while(curr != NULL){
      tmp = curr;
      curr = curr->next;
      free(tmp);
    }
    //printf("free ptr[%d]\n", i);
  }
  free(ptr);
  printf("Clear members' info...\n");
}

/*
 * This function frees all allocated space in the timeslot array
 */
void destroy_slot_list(slot * ptr){
  int i;
  for (i = slot_list_size - 1; i >= 0; i--)
    free((ptr+i)->time);
  free(ptr);
  printf("Clear timeslot array...\n");
}

/*
 * This function finds all matched members for every timeslot
 */
void find_match_member(slot * slot, mem * list){
  int i, j, k;
  int day, start, end;
  period * curr;
  for (i = 0; i < slot_list_size; i++){
    k = 0;
    day = (slot + i)->time->day;
    start = (slot + i)->time->start_time;
    end = (slot + i)->time->end_time;
    for (j = 0;j < mem_list_size; j ++){
      curr = (list + j)->time;
      while (curr != NULL){
        if (day == curr->day && start >= curr->start_time && end <= curr->end_time){
          (slot + i)->fit_index[k] = j + 1;
          k++;
          break;
        }
        curr = curr->next;
      }
    }
  }
}

/* 
 * This function checks whether it is possible to generate a schedule
 * by checking if each timeslot has some matched members
 * Return 0 is impossible to generate a schedule, 1 otherwise
 */
int check_possible_schedule(slot * slot){
  int i;
  for(i = 0; i < slot_list_size; i++)
    if ((slot+i)->fit_index[0] == 0)
      return 0;
  return 1;
}

/*
 * This function uses back-tracking recursion to generate a  
 * possible schedule
 */
int generator(slot * slot, mem * list){
  if (slot + 1 == NULL){ 
    if(list->availability == 1){
      slot->final_index = list->index;
      return 1;
    }else{
      return 0;
    }
  }

}
