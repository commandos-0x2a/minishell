#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <readline/readline.h>

void signal_handler(int signum)
{
    close(0);
}

int main()
{
    struct termios orig_termios, raw_termios;
    tcgetattr(0, &orig_termios);
    raw_termios = orig_termios;
    raw_termios.c_lflag &= ~ECHOCTL;
    tcsetattr(0, TCSANOW, &raw_termios);

    // struct sigaction sa;
    // sa.sa_handler = signal_handler;
    // sa.sa_flags = 0;
    // sigemptyset(&sa.sa_mask);
    // sigaction(SIGINT, &sa, NULL);

    signal(SIGINT, signal_handler);

    while (1)
    {
        if (!isatty(0))
            dup2(2, 0);
        char *line = readline("> ");
        printf("%s \n", line);
        if (!line && !isatty(0))
            continue; // ^C
        if (!line)
            break; // ^D

    }
}