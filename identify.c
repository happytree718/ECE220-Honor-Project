# include <stdio.h>
# include <stdlib.h>

typedef struct worker{
  char name[10];
  int day;
  int start_time;
  int end_time;
  int availability;
}mem;

typedef struct timeslot{
  int day;
  int start_time;
  int end_time;
  int num_member;
  int filled;
}slot;

int main(){
  
}
