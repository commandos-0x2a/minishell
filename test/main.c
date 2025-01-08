#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(void)
{
	void *ptr = malloc(100);
	char **argv = calloc(2, sizeof(char *));

	argv[0] = "echo";
	argv[1] = NULL;

	int pid = fork();
	if (pid == 0)
	{
		execve("/bin/echo", argv, NULL);
		exit(0);
	}
	free(argv);
	wait(NULL);
	free(ptr);
	return (0);
}
