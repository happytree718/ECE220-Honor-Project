#include <signal.h>

typedef struct timeperiod{
  int day;
  int start_time;
  int end_time;
  period * next;
}period;

/*
 *
 */
typedef struct worker{
  char name[10];
  period * time;
  int availability;
}mem;

/*
 *
 */
typedef struct timeslot{
  period * time;
  int num_member;
  int filled;
}slot;

/*
 */
int start_time_to_index(int n);
/*
 */
int end_time_to_index(int n);
mem * member_input();
slot * timeslot_input();
mem * file_member_input(char* file);
slot * file_timeslot_input(char* file);