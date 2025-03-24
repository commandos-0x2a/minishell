#include <unistd.h>
#include <stdio.h>

int main()
{
	char	*argv[] = {
		"./victim.elf",
		NULL
	};
	execve("./victim.elf", argv, NULL);
	perror("execve");
	return (1);
}
