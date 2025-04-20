#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <bits/sigaction.h>
#include <sys/wait.h>

volatile int    g_status;

void    signal_handler(int sig)
{
    char    buf[1024];
    g_status = sig;
    ssize_t _read = read(0, buf, sizeof(buf));
    printf("[%s] read: %zd\n", __func__, _read);
}

void    setup_signals()
{
    struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

int main()
{
    char    buf[1024];

    g_status = 0;
    setup_signals();
    if (fork() == 0)
    {
        ssize_t _read = read(0, buf, sizeof(buf));
        printf("[%s] read: %zd\n", __func__, _read);
        printf("g_status: %d\n", g_status);
    }
    wait(NULL);
}