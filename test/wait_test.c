#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

union wait	status;
pid_t		pid;

#define PRINT_STATUS 				\
	fprintf(stderr, "%s (%d):\n"	\
		"\tw_termsig: %d\n"			\
		"\tw_coredump: %d\n"		\
		"\tw_retcode: %d\n"			\
		"\tw_stopval: %d\n"			\
		"\tw_stopsig: %d\n",		\
		__func__,					\
		pid,						\
		status.w_termsig,			\
		status.w_coredump,			\
		status.w_retcode,			\
		status.w_stopval,			\
		status.w_stopsig			\
	)
#define PRINT_DASH					\
	for (int i = 0; i < 18; i++)	\
		write(2, "-", 1);			\
	write(2, "\n\n", 2);			\

void	exit_test()
{
	if ((pid = fork()) == 0)
		exit(10);
	waitpid(pid, &status.w_status, 0);
	PRINT_STATUS;
}

void	signal_test()
{
	if ((pid = fork()) == 0)
	{
		kill(getpid(), SIGKILL);
		exit(1);
	}
	waitpid(pid, &status.w_status, 0);
	PRINT_STATUS;
}

void	stop_cont_test()
{
	if ((pid = fork()) == 0)
	{
		kill(getpid(), SIGSTOP);
		exit(1);
	}
	waitpid(pid, &status.w_status, WUNTRACED);
	PRINT_STATUS;
	kill(pid, SIGCONT);
	waitpid(pid, &status.w_status, WUNTRACED);
	PRINT_STATUS;
}

void	tty_stop_cont_test()
{
	if ((pid = fork()) == 0)
	{
		kill(getpid(), SIGTSTP);
		exit(1);
	}
	waitpid(pid, &status.w_status, WUNTRACED);
	PRINT_STATUS;
	kill(pid, SIGCONT);
	waitpid(pid, &status.w_status, WUNTRACED);
	PRINT_STATUS;
}

void	sigbus_test()
{
	if ((pid = fork()) == 0)
	{
		""[0] = 'A';
		exit(1);
	}
	waitpid(pid, &status.w_status, 0);
	PRINT_STATUS;
}

int main()
{
	void	(*test_funcs[])() = {
		exit_test,
		signal_test,
		stop_cont_test,
		tty_stop_cont_test,
		sigbus_test
	};
	for (int i = 0; i < sizeof(test_funcs) / sizeof(*test_funcs); i++)
	{
		test_funcs[i]();
		PRINT_DASH;
	}
	return (0);
}