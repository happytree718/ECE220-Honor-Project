
/*
 */
typedef struct timetable
{
  char day[20];
  char* time[28];
  /* from 8am to 10pm, each array 
   * represent the person for this
   * half-hour period
   */
}agenda;

/*
 */
void print_table(agenda *array);
/*
 */
void file_print_table(agenda *array);


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
