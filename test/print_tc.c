#include <unistd.h>
#include <termios.h>

void	main()
{
	struct termios term;
    // long            vdisable;

	// vdisable = fpathconf(STDIN_FILENO, _PC_VDISABLE);

    tcgetattr(STDIN_FILENO, &term);

	printf("VEOF:     %u	# %s\n",		term.c_cc[VEOF],      " ICANON");
	printf("VEOL:     %u	# %s\n",		term.c_cc[VEOL],      " ICANON");
	printf("VEOL2:    %u	# %s\n",		term.c_cc[VEOL2],     " ICANON together with IEXTEN");
	printf("VERASE:   %u	# %s\n",		term.c_cc[VERASE],    " ICANON");
	printf("VWERASE:  %u	# %s\n",		term.c_cc[VWERASE],   " ICANON together with IEXTEN");
	printf("VKILL:    %u	# %s\n",		term.c_cc[VKILL],     " ICANON");
	printf("VREPRINT: %u	# %s\n",		term.c_cc[VREPRINT],  " ICANON together with IEXTEN");
	printf("VINTR:    %u	# %s\n",		term.c_cc[VINTR],     " ISIG");
	printf("VQUIT:    %u	# %s\n",		term.c_cc[VQUIT],     " ISIG");
	printf("VSUSP:    %u	# %s\n",		term.c_cc[VSUSP],     " ISIG");
	printf("VDSUSP:   %u	# %s\n",		term.c_cc[VDSUSP],    " ISIG together with IEXTEN");
	printf("VSTART:   %u	# %s\n",		term.c_cc[VSTART],    " IXON, IXOFF");
	printf("VSTOP:    %u	# %s\n",		term.c_cc[VSTOP],     " IXON, IXOFF");
	printf("VLNEXT:   %u	# %s\n",		term.c_cc[VLNEXT],    " IEXTEN");
	printf("VDISCARD: %u	# %s\n",		term.c_cc[VDISCARD],  " IEXTEN");
	printf("VMIN:     %u	# %s\n",		term.c_cc[VMIN],      " !ICANON");
	printf("VTIME:    %u	# %s\n",		term.c_cc[VTIME],     " !ICANON");
	printf("VSTATUS:  %u	# %s\n",		term.c_cc[VSTATUS],   " ICANON together with IEXTEN");


	printf("ECHOKE:  %d  # %s\n",        !!(term.c_lflag & ECHOKE),      " visual erase for line kill");
	printf("ECHOE:   %d  # %s\n",         !!(term.c_lflag & ECHOE),       " visually erase chars");
	printf("ECHOK:   %d  # %s\n",         !!(term.c_lflag & ECHOK),       " echo NL after line kill");
	printf("ECHO:    %d  # %s\n",          !!(term.c_lflag & ECHO),        " enable echoing");
	printf("ECHONL:  %d  # %s\n",        !!(term.c_lflag & ECHONL),      " echo NL even if ECHO is off");
	printf("ECHOPRT: %d  # %s\n",       !!(term.c_lflag & ECHOPRT),     " visual erase mode for hardcopy");
	printf("ECHOCTL: %d  # %s\n",       !!(term.c_lflag & ECHOCTL),     " echo control chars as ^(Char)");
	printf("ISIG:    %d  # %s\n",          !!(term.c_lflag & ISIG),        " enable signals INTR, QUIT, [D]SUSP");
	printf("ICANON:  %d  # %s\n",        !!(term.c_lflag & ICANON),      " canonicalize input lines");
	printf("IEXTEN:  %d  # %s\n",        !!(term.c_lflag & IEXTEN),      " enable DISCARD and LNEXT");
	printf("EXTPROC: %d  # %s\n",       !!(term.c_lflag & EXTPROC),     " external processing");
	printf("TOSTOP:  %d  # %s\n",        !!(term.c_lflag & TOSTOP),      " stop background jobs from output");
	printf("FLUSHO:  %d  # %s\n",        !!(term.c_lflag & FLUSHO),      " output being flushed (state)");
	printf("PENDIN:  %d  # %s\n",        !!(term.c_lflag & PENDIN),      " XXX retype pending input (state)");
	printf("NOFLSH:  %d  # %s\n",        !!(term.c_lflag & NOFLSH),      " don't flush after interrupt");
	printf("ALTWERASE:  %d  # %s\n",     !!(term.c_lflag & ALTWERASE),   " use alternate WERASE algorithm");
	printf("NOKERNINFO: %d  # %s\n",    !!(term.c_lflag & NOKERNINFO),  " no kernel output from VSTATUS");

    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

