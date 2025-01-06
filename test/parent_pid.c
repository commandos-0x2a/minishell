#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc == 2)
		printf("%s: ", argv[1]);
	printf("%d\n", getppid());
}