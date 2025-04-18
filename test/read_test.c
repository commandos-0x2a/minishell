#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

volatile int	g_sig;

void	signal_handler(int signum)
{
	g_sig = signum;
}

int	simple_here_doc()
{
	int 	nbytes;
	char	*line;
	ssize_t	_read;

	write(1, "> ", 2);
	while (1)
	{
		if (ioctl(STDIN_FILENO, FIONREAD, &nbytes) == -1)
		{
			perror("FIONREAD");
			return (-1);
		}
		if (g_sig != 0)
			return (0);
		if (nbytes > 0)
		{
			printf("nbytes: %d\n", nbytes);
			line = malloc(nbytes + 1);
			if (!line)
				return (-1);	// Allocation failed
			_read = read(STDIN_FILENO, line, nbytes);
			if (_read < 0)
				return (-1);	// Error
			if (_read == 0)
				return (0);		// EOF
			line[_read] = '\0';
			write(1, "> ", 2);
		}
	}
	return (0);
}

int main()
{
	int	err;
	int	wstatus;

	g_sig = 0;
	signal(SIGINT, signal_handler);
	if (fork() == 0)
	{
		err = simple_here_doc();
		if (err < 0)
			perror("read");
		if (g_sig != 0)
			exit(128 + g_sig);
		exit(0);
	}
	while (wait(&wstatus) != -1)
		;
	if (WIFEXITED(wstatus))
		printf("exited by %d\n", WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		printf("signaled by %d\n", WTERMSIG(wstatus));
}