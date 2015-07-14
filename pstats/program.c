#define _GNU_SOURCE

#include <stdio.h>
#include <sys/types.h>
#include <sched.h>
#include <limits.h>

int main(int argc, char* argvi[])
{
  	pid_t pid = getpid();

		
	  cpu_set_t my_set;
    int ret;
    CPU_ZERO(&my_set);
		CPU_SET(1, &my_set);
		CPU_SET(2, &my_set);

    ret = sched_setaffinity(0, 1, &my_set);
	  if (ret < 0)
	  {
		  printf("error");
	  }
	  
	  ret = sched_getaffinity(0, 1, &my_set);
		printf("pid %d affinity includes CPUs ... ", pid);
		int j;
		for (j = 0; j < 4; ++j)
		{
			if (CPU_ISSET(j, &my_set))
			{
				printf("%d ",j);
			}

		}
		//printf ("pid %d aiffinity %lx\n", pid, my_set);

		/*
	  long x = 0;
	  long i;	
	  while (i < LONG_MAX)
	  {
	  	x += i;
	  	++i;
	  }
	  printf("%ld\n",x);*/

		printf("hello");
	  return 0;
}

