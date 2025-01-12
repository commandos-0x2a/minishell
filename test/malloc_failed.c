#include <stdlib.h>
#include <stdio.h>

int main()
{
	void *ptr = malloc(128);
	printf("%p\n", ptr);
}