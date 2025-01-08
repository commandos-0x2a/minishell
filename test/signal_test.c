#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *handler(int sig)
{
	printf("Signal %d\n", sig);
}


int	main(void)
{
	signal(SIGINT, handler);
	sleep(120);
	return 0;
}
