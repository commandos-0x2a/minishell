#include <stdio.h>

// make a core dump to test the core dump failure
#include <signal.h>
#include <stdlib.h>

void handle_signal(int sig) {
	signal(sig, SIG_DFL);
	abort();
}

void setup_handlerWs(void) {
	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);
	signal(SIGQUIT, handle_signal);
}

int main(void)
{
	setup_handlerWs();
	while (1);
	return 0;
}
