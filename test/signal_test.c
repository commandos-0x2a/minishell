#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
[SIGCHLD]
si_pid,
si_uid,
si_status,
si_utime,
si_stime,

providing information about the child.  
- si_pid: field is the process ID of the child; 
- si_uid: the child's real user ID.
- si_status: field contains the exit status of the child (if si_code is CLD_EXITED), 
	or the signal number that caused the process to change state.
*/
void sigchld_handler(int signum, siginfo_t *info, void *context)
{
	pid_t	pid;

	printf("---------------\n");
	printf("si_pid: %d\n", info->si_pid);
	printf("si_uid: %d\n", info->si_errno);
	printf("si_status: %d\n", info->si_status);
	pid = waitpid(info->si_pid, NULL, 0);
	printf("waitpid: %d\n", pid);
}

int main()
{
	struct sigaction act;

	/* Install SIGCHLD handler */
	memset(&act, 0, sizeof(act));
	act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = sigchld_handler;
	if (sigaction(SIGCHLD, &act, NULL) != 0)
	{
		perror("signal");
		exit(1);
	}

	for (int i = 0; i < 8; i++)
	{
		if (fork() == 0)
		{
			sleep(i + 1);
			exit(0);
		}
	}
	while (pause())
		;
	return (0);
}