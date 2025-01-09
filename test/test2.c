#include <termios.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static struct termios       save_termios;



int	tty_raw(int fd) /* put terminal into a raw mode */
{
	int				err;
	struct termios	buf;

	if (tcgetattr(fd, &buf) < 0)
		return(-1);
	save_termios = buf; /* structure copy */
	/*
		* Echo off, canonical mode off, extended input
		* processing off, signal chars off.
	*/
	buf.c_lflag &=  ~(ECHO | ICANON | IEXTEN | ISIG);
	// buf.c_lflag &= ~(ECHOCTL | ISIG);
	/*
		* No SIGINT on BREAK, CR-to-NL off, input parity
		* check off, don’t strip 8th bit on input, output
		* flow control off.
	*/
	// buf.c_iflag &=  ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	/*
		* Clear size bits, parity checking off.
	*/
	// buf.c_cflag &=  ~(CSIZE | PARENB);
	/*
		* Set 8 bits/char.
	*/
	// buf.c_cflag |= CS8;
	/*
		* Output processing off.
	*/
	// buf.c_oflag &=  ~(OPOST);
	/*
	* Case B: 1 byte at a time, no timer.
	*/
	// buf.c_cc[VMIN] = 1;
	// buf.c_cc[VTIME] = 0;
	if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
		return(-1);
    return(0);
}

int	tty_reset(int fd)
{
	if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
		return(-1);
	return(0);
}







static void	sig_catch(int signo)
{
    printf("signal caught\n");
    tty_reset(STDIN_FILENO);
    exit(0);
}

void	err_sys(const char *msg)
{
	perror(msg);
	exit(1);
}

int main()
{
	int		i;
	char	c;

	if (signal(SIGINT, sig_catch) == SIG_ERR)
		err_sys("signal(SIGINT) error");
	if (signal(SIGQUIT, sig_catch) == SIG_ERR)
		err_sys("signal(SIGQUIT) error");
	if (signal(SIGTERM, sig_catch) == SIG_ERR)
		err_sys("signal(SIGTERM) error");

	if (tty_raw(STDIN_FILENO) < 0)
		err_sys("tty_raw error");
	
	while ((i = read(STDIN_FILENO, &c, 1)) == 1)
	{
		if ((c &= 255) == 0177) /* 0177 = ASCII DELETE */
			break;
		printf("%o\n", c);
	}
	if (tty_reset(STDIN_FILENO) < 0)
		err_sys("tty_reset error");
	exit(0);
}