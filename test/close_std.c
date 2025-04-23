#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void	run_lsof()
{
	char	pid_str[12];

	snprintf(pid_str, sizeof(pid_str), "%d", getpid());
	if (fork() == 0)
	{
		usleep(1000);
		char *lsof_argv[] = {
			"lsof",
			"-w",
			"-g",
			pid_str,
			NULL,
		};

		execve("/usr/sbin/lsof", lsof_argv, NULL);
		exit(1);
	}
}

int main()
{
	char	*ttypath;
	char	buf[1024];
	
	
	ttypath = ttyname(0);
	printf("ttypath: %s\n", ttypath);


	close(0);

	run_lsof();

	int fd = open(ttypath, O_RDONLY);
    if (fd != 0) {
		// If the new FD is not 0, duplicate it to 0
        dup2(fd, 0);
        close(fd);
    }

	wait(NULL);



	read(0, buf, sizeof(buf));

	run_lsof();
	wait(NULL);
}