
/*
 */
typedef struct timetable
{
  char *day;
  int start_time;
  int end_time;
  char *time[28];
  /* from 8am to 10pm, each array represent the person for this
   * half-hour period
   */
}agenda;
/*
 */
void print_table(agenda *array);
/*
 */
int hour(int n);
/*
 */
int min(int n);
/*
 */
void line();
/*
 */
void fence();
