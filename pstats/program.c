#define _GNU_SOURCE

#include <stdio.h>
#include <sys/types.h>
#include <sched.h>
#include <limits.h>

int main(int argc, char* argvi[])
{
  	pid_t pid = getpid();

	cpu_set_t my_set;
    pid_t p = getpid();
    int ret;
    //CPU_ZERO(&my_set);

    ret = sched_getaffinity(0, sizeof(cpu_set_t), &my_set);
	if (ret < 0)
	{
		printf("error");
	}
	printf ("pid %d affinity %llx\n", pid, my_set);

	long x = 0;
	long i;	
	while (i < LONG_MAX)
	{
		x += i;
		++i;
	}
	printf("%ld\n",x);
	return 0;
}


