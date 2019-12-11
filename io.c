# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "print.h"
# include "io.h"

int mem_list_size, slot_list_size;

mem * member_input(){
  // input for member info
  int m, i = -1;
  char type;
  period * time;
  printf("Please enter the number of total members:\n");
  scanf("%d", &m);
  //const int a = m;
  mem * list = (mem *)malloc(m * sizeof(mem));
  mem_list_size = m;
  while(m >= 0){
    printf("info type identifier:(N/T)\n");
    scanf("%c", &type);
    if (type == 'N'){
      i++;
      m--;
      if(m == -1) break;
      printf("Name:\n");
      scanf("%s", (list+i)->name);
    }else if (type == 'T'){
      printf("Available time slot detail:\n");
      time = (period *)malloc(sizeof(period));
      scanf("%d %d %d", &(time->day), &(time->start_time), &(time->end_time));
      time->next = (list+i)->time;
      (list+i)->time = time;
    }
  }
  // for (m = 0; m < a; m++){
  //   (list + m)->name = (char*) malloc(10 * sizeof(char));
  //   printf("Name: \n");
  //   scanf("%s", (list+m)->name);
  //   printf("What day? ('0' for Sunday ~ '6' for Sunday)\n");
  //   scanf("%d", &(list+m)->day);
  //   printf("Start time and end time: \n");
  //   scanf("%d %d", &(list+m)->start_time, &(list+m)->end_time);
  //   (list+m)->availability = 1;
  // }
  return list;
}

slot * timeslot_input(){
  // input for timeslot info
  int m;
  printf("Please enter the number of total timeslots:\n");
  scanf("%d", &m);
  slot_list_size = m;
  const int b = m;
  slot * time = (slot *) malloc (b * sizeof(slot));
  printf("Please input time slot info below\n");
  for (m = 0; m < b; m++){
    (time+m)->time = malloc(sizeof(period));
    printf("What day? ('0' for Sunday ~ '6' for Sunday)\n");
    scanf("%d", &((time[m].time)->day));
    printf("Start time and end time: \n");
    scanf("%d %d", &time[m].time->start_time, &time[m].time->end_time);
    printf("Number of members per slot: \n");
    scanf("%d", &time[m].num_member);
    (time + m)->filled = 0;
  }
  return time;
}



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
 * This function prints the member list
 */
void print_mem_list(mem * mem){
  int i = 0;
  period * time;
  printf("The following is the member list:\n");
  for (; i < mem_list_size; i++){
    printf("%s\n",mem[i].name);
    time = mem[i].time;
    while (time != NULL){
      printf("Day%d: %d-%d\n", time->day, time->start_time, time->end_time);
      time = time->next;
    }
  }
  return;
}
// This function prints the slot list.
void print_slot_list(slot * slot){
  int i = 0;
  printf("The following is the slot list:\n");
  for (; i < slot_list_size; i++){
    printf("Day%d: %d-%d\n", (slot+i)->time->day, (slot+i)->time->start_time, (slot+i)->time->end_time);
  }
  return;
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
 * and stores in fit_index with (index number +1) so that 
 * we avoid ambuguity between 0 index and no fit.
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
    printf("i = %d\n", i);
    for (j = 0;j < mem_list_size; j ++){
      curr = (list + j)->time;
      while (curr != NULL){
        if (day == curr->day && start >= curr->start_time && end <= curr->end_time){
          (slot + i)->fit_index[k] = j + 1;
          printf("%d\n", (slot + i)->fit_index[k]);
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
    if ((slot+i)->fit_index[0] == 0) return 0;
  return 1;
}

/*
 * This function uses back-tracking recursion to match each 
 * time slot with a member. 
 */
int GenerateSchedule(slot * slot, int * nth, mem * member){
  int i = 0;
  if (*nth >= slot_list_size) return 0;
  for (; slot->fit_index[i] != 0; i++){
    //printf("%d out:%d\n",*nth, i);
    if (member[(slot->fit_index[i]-1)].availability == 1){
      //printf("%d %d\n", *nth, slot->fit_index[i]);
      slot->filled = slot->fit_index[i];
      member[(slot->fit_index[i]-1)].availability = 0;
       // base case
      if (*nth == slot_list_size-1) return 1;
      // recursive case
      *nth = *nth + 1;
      if (GenerateSchedule(slot+1, nth, member)){ 
        //printf("%d %dworked\n", *nth, slot->fit_index[i]);
        return 1;
      }else{
        //printf("%d %dfailed\n", *nth, slot->fit_index[i]);
        slot->filled = 0;
        *nth = *nth - 1;  
        member[(slot->fit_index[i]-1)].availability = 1;
      }
    }
  }
  return 0; 
}

void assign_table(agenda * day, slot* slot, mem * list){
  int i = 0, j;
  int day_, start, end;
  char name[10];
  for(; i < slot_list_size; i++){
    //printf("%d\n", (slot+i)->filled);
    start = start_time_to_index((slot+i)->time->start_time);
    end = end_time_to_index((slot+i)->time->end_time);
    day_ = (slot+i)->time->day;
    strcpy(name, list[(slot+i)->filled-1].name);
    for(j = start; j <= end; j++){
      //day[day_].time[j] = list[(slot+i)->filled-1].name;
      //mem m;
      //char test[10] =  "abcd";
      //strcpy(m.name, list[(slot+i)->filled-1].name);
      strcpy(day[day_].time[j], name);
      //printf("%s\n", day[day_].time[j]);
    }
  }
  return;  
}
