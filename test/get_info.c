#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	printf("pid: %d\n", getpid());
	printf("ppid: %d\n", getppid());
	printf("gpid: %d\n", getgid());
	printf("pgrp: %d\n", getpgrp());
}