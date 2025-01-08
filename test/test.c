#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int pid;

	pid = fork();
	if (pid == 0)
		exit(1);

	int status;
	status = 123;
	printf("pid: %d, status: %d\n", wait(&status), status);
	printf("pid: %d, status: %d\n", wait(&status), status);
}