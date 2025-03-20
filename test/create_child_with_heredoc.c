

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <signal.h>
#include <sys/wait.h>

void sigchld_handler(int signum)
{
    int wstatus;

    if (wait(&wstatus) == -1)
        exit(1);
    printf("[parent]: catch %d\n", wstatus);
    if (wait(&wstatus) == -1)
        exit(1);
    printf("[parent]: catch %d\n", wstatus);
    exit(0);
}


void signal_handler(int signum)
{

}

int main()
{
    char buf[16];

    printf("test\n");
    /* Install SIGCHLD handler */
	if (signal(SIGCHLD, sigchld_handler) < 0) {
		perror("signal");
		exit(1);
	}

     /* Install SIGCHLD handler */
	if (signal(SIGCHLD, ) < 0) {
		perror("signal");
		exit(1);
	}


    if (fork() == 0)
    {
        ssize_t _read;
    
        write(1, "[child] read: ", 14);
        _read = read(0, buf, sizeof(buf) - 1);
        kill(getppid(), SIGUSR1);
        buf[_read] = '\0';
        printf("[child]: wait 5 second ...\n");
        sleep(5);
        printf("[child]: read (%zd): %s\n", _read, buf);
        exit(0);
    }
    while (pause())
        ;
    return (0);
}