#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#define MAX_PASS_LEN    8


char    *getpass(const char *);
int		err_sys(char *msg)
{
	perror(msg);
	exit(1);
}

int	main(void)
{
	char *ptr;
	if ((ptr = getpass("Enter password:")) == NULL)
		err_sys("getpass error");
	printf("password: %s\n", ptr);
	/* now use password (probably encrypt it) ... */
	while (*ptr != 0)
		*ptr++ = 0;     /* zero it out when we’re done with it */
	exit(0);
}

char	*getpass(const char *prompt)
{
	/* max #chars for user to enter */
    static char		buf[MAX_PASS_LEN + 1];
    char			*ptr;
    sigset_t		sig, osig;
    struct termios  ts, ots;
    FILE            *fp;
    int             c;

	printf("ctermid: %s\n", ctermid(NULL));


    if ((fp = fopen(ctermid(NULL), "r+")) == NULL)
        return(NULL);
    setbuf(fp, NULL);
    sigemptyset(&sig);
    sigaddset(&sig, SIGINT);        /* block SIGINT */
    sigaddset(&sig, SIGTSTP);       /* block SIGTSTP */
    sigprocmask(SIG_BLOCK, &sig, &osig);    /* and save mask */
    tcgetattr(fileno(fp), &ts);     /* save tty state */
    ots = ts;                       /* structure copy */
    ts.c_lflag &=  ~(ECHO | ECHOE | ECHOK | ECHONL);
    tcsetattr(fileno(fp), TCSAFLUSH, &ts);
    fputs(prompt, fp);
    ptr = buf;
    while ((c = getc(fp)) != EOF && c != '\n')
        if (ptr < &buf[MAX_PASS_LEN])
            *ptr++ = c;
    *ptr = 0;           /* null terminate */
    putc('\n', fp);     /* we echo a newline */
    tcsetattr(fileno(fp), TCSAFLUSH, &ots); /* restore TTY state */
    sigprocmask(SIG_SETMASK, &osig, NULL);  /* restore mask */
    fclose(fp);         /* done with /dev/tty */
    return(buf);
}