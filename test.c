#include <string.h>
#include <stdio.h>

int main()
{
	char	*str = "AAA";

	char *null = strchr(str, '\0');
	printf("null: %s\n", null);
}