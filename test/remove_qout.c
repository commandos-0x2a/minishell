#include <stdio.h>

void	remove_qouts(char *src)
{
	char	*dst;
	char	qout;

	dst = src;
	qout = '\0';
	while (*src)
	{
		if ((*src == '\'' || *src == '\"') \
			&& (qout == *src || qout == '\0'))
		{
			if (!qout)
				qout = *src;
			else
				qout = '\0';
			src++;
			continue ;
		}
		*dst++ = *src++;
	}
	*dst = '\0';
	return (src);
}

int main()
{
	char	line[] = "AAAAAAA'BBBBBBB'\"CCCCCCC'DDDDD'EEEEE\"FFFF";

	printf("%s\n", line);
	remove_qouts(line);
	printf("%s\n", line);
}