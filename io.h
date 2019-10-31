#include <signal.h>
/*
 *
 */
typedef struct worker{
  char *name;
  int day;
  int start_time;
  int end_time;
  int availability;
}mem;

/*
 *
 */
typedef struct timeslot{
  int day;
  int start_time;
  int end_time;
  int num_member;
  int filled;
}slot;

/*
 */
int start_time_to_index(int n);
/*
 */
int end_time_to_index(int n);
