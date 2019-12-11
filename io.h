# include <signal.h>

typedef struct timeperiod period;

typedef struct timeperiod{
  int day;
  int start_time;
  int end_time;
  period * next;
}period;

typedef struct worker{
  char name[10];
  period * time;
  int availability;
  int index;
}mem;

typedef struct timeslot{
  period * time;
  int num_member;
  int filled;
  int fit_index[50];
}slot;

/*
 */
int start_time_to_index(int n);
/*
 */
int end_time_to_index(int n);

mem * member_input();
slot * timeslot_input();

void print_mem_list(mem * mem);
void print_slot_list(slot * slot);

mem * file_member_input(char* file);
slot * file_timeslot_input(char* file);
void destroy_mem_list(mem * ptr);
void destroy_slot_list(slot * ptr);
void find_match_member(slot * slot, mem * list);
int check_possible_schedule(slot * slot);
int GenerateSchedule(slot * slot, int * nth, mem * member);
void assign_table(agenda * day, slot * slot, mem * list);