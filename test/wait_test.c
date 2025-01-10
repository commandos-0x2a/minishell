#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

#define TEST(pid, baby_pid) (pid == baby_pid ? "baby" : "sitter")

pid_t	baby(int play_time)
{
	pid_t	pid;
	int 	i;

	if ((pid = fork()) == 0)
	{
		i = 0;
		while (i < play_time)
		{
			printf("- baby play: %i\n", i);
			sleep(1);
			i++;
		}
		exit(1);
	}
	return (pid);
}

pid_t	baby_sitter(pid_t baby)
{
	pid_t pid;

	if ((pid = fork()) == 0)
	{
		sleep(2);            // baby play to 2 second
		kill(baby, SIGSTOP); // baby sleep
		sleep(10);           // baby sleep to 10 second
		kill(baby, SIGCONT); // baby wake up
		sleep(5);            // sitter wait for 2 second before leave

		exit(0);
	}
	return (pid);
}

int main()
{
	pid_t 	pid;
	pid_t	baby_pid;
	pid_t	sitter_pid;
	int		wstatus;

	baby_pid 	= baby(12);
	sitter_pid 	= baby_sitter(baby_pid);

	while ((pid = waitpid(WAIT_ANY, &wstatus, WNOHANG | WUNTRACED | WCONTINUED)) != -1)
	{
		if (pid == 0)
			continue;
		if (WIFEXITED(wstatus))
		{
			if (WEXITSTATUS(wstatus) == 0)
				printf("%d: Exited %d   # %s leave\n", \
						pid, WEXITSTATUS(wstatus), TEST(pid, baby_pid));
			else 
				printf("%d: Exited %d   # %s died\n", pid, \
						WEXITSTATUS(wstatus), TEST(pid, baby_pid));
		}
		else if (WIFCONTINUED(wstatus))
			printf("%d: Continued   # %s wake up\n", \
					pid, TEST(pid, baby_pid));
		else if (WIFSTOPPED(wstatus))
			printf("%d: Stopped %d  # %s sleep\n", pid, \
					WSTOPSIG(wstatus), TEST(pid, baby_pid));
		else if (WIFSIGNALED(wstatus))
		{
			if (WCOREDUMP(wstatus))
				printf("%d: COREDUMP 		# %s was killed\n", \
						pid, TEST(pid, baby_pid));
			else
				printf("%d: Signaled by %d  # %s was shocked\n", \
						pid , WTERMSIG(wstatus), TEST(pid, baby_pid));
		}
		else
			printf("%d: WOW\n", pid);
	}
}