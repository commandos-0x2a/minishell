#include <string.h>
#include <stdio.h>

int main()
{
	int num[16];
	memset(num, -1, sizeof(num));

	for (int i = 0; i < sizeof(num) / sizeof(*num); i++)
		printf("num[%d]: %d\n", i, num[i]);
	return (0);
}