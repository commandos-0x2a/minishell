#include <stdio.h>
#include <string.h>
#include <stdlib.h>


size_t	operation_len(const char *s)
{
	if (strncmp(s, "&&", 2) == 0 || strncmp(s, "||", 2) == 0 \
		|| strncmp(s, ">>", 2) == 0 || strncmp(s, "<<", 2) == 0)
		return (2);
	else if (*s == '|' || *s == '<' || *s == '>')
		return (1);
	return (0);
}

size_t	get_new_len(const char *s)
{
	size_t	len;
	size_t	op_len;

	len = strlen(s);
	while (*s)
	{
		op_len = operation_len(s);
		if (op_len)
		{
			s += op_len - 1;
			len += 2;
		}
		else if (*s == '\'' || *s == '"')
			s = strchr(s + 1, *s);
		if (!s || !*s)
			break;
		s++;
	}
	return (len);
}

void	copy_line(char *dst, const char *src)
{
	size_t	op_len;
	char	qout;

	op_len = 0;
	qout = '\0';
	while (*src)
	{
		if (*src == qout)
			qout = '\0';
		else if ((*src == '\'' || *src == '\"') && !qout)
			qout = *src;
			
		if (op_len == 0 && !qout)
		{
			op_len = operation_len(src);
			if (op_len)
				*dst++ = ' ';
		}

		*dst++ = *src++;

		if (qout)
			continue ;
		
		if (op_len == 1)
			*dst++ = ' ';
		if (op_len > 0)
			op_len--;
	}
	*dst = '\0';
}

char	*add_space_to_line(const char *s)
{
	size_t	len;
	char	*newline;

	len = get_new_len(s);
	if (!s)
		return (NULL);
	newline = malloc(len + 1);
	if (!newline)
		return (NULL);
	newline[0] = '\0';
	copy_line(newline, s);
	return (newline);
}
