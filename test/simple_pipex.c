#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv, char **env_p)
{
	if (fork() == 0)
	{
		// int out_fd = open("out", O_WRONLY | O_CREAT, 0644);
		// dup2(out_fd, STDOUT_FILENO);
		// close(out_fd);

		// int in_fd = open("in", O_RDONLY);
		// dup2(in_fd, STDIN_FILENO);
		// close(in_fd);

		char *cmd_argv[] = {
			"echo",
			"child1",
			NULL
		};
		execve("/bin/echo", cmd_argv, env_p);
		perror("execve");
		exit(1);
	}
	if (fork() == 0)
	{
		// int out_fd = open("out", O_WRONLY | O_CREAT, 0644);
		// dup2(out_fd, STDOUT_FILENO);
		// close(out_fd);

		// int in_fd = open("in", O_RDONLY);
		// dup2(in_fd, STDIN_FILENO);
		// close(in_fd);

		char *cmd_argv[] = {
			"echo",
			"child2",
			NULL
		};
		execve("/bin/echo", cmd_argv, env_p);
		perror("execve");
		exit(1);
	}
}