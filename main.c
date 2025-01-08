#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int pid = getppid();
	printf("%d\n", pid);
	return (0);
}