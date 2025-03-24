#include <unistd.h>
#include <stdio.h>

/*
	pid is same main pid
*/

int main()
{
	printf("pid: %d\n", getpid());
	return (0);
}
