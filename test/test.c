#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char *value = getenv("TEST");

	printf("argc: %d\n", argc);
	printf("value: %s\n", value);
}