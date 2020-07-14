#include <sys/types.h>
//#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <stdio.h>

int main()
{
  int pid;
  timespec time;
  
  // Gets the round robin scheduler time slice interval
  // You can read about this by typing "man 2 sched_rr_get_interval"
  int result = sched_rr_get_interval(0,&time);
  
  printf("Time (seconds) %ld\n",time.tv_nsec);

  return 0;
}
