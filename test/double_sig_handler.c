
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

unsigned long start;


unsigned long	get_time_now()
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void signal_handler(int signum)
{
	sleep(2);
	printf("%ld end wait\n", get_time_now() - start);
    start = get_time_now();
	return;
}



int main()
{
    start = get_time_now();
    signal(SIGINT, signal_handler);
    while (pause())
        ;
}