#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int with_pipe(char *cmd1, char *cmd2);
int with_file(char *cmd1, char *cmd2);

void print_usage(char *program_name)
{
	fprintf(stderr, "Usage: %s {pipe|file} cmd1 cmd2\n", program_name);
	exit(1);
}

int main(int argc, char **argv)
{
	if (argc != 4)
		print_usage(argv[0]);
	if (strcmp(argv[1], "file") == 0)
		return (with_file(argv[2], argv[3]));
	else if (strcmp(argv[1], "pipe") == 0)
		return (with_pipe(argv[2], argv[3]));
	else
		print_usage(argv[0]);
}

/*
$ ./a.out file "echo test" "cat -e"  # don't print test !!!
$ ./a.out file "echo test" "cat -e"
test$
$ ./a.out file "echo test" "cat -e"
test$
$ ./a.out file "echo test" "cat -e"  # don't print test !!!!
*/