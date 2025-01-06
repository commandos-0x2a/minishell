#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

typedef struct s_var
{
	char	*name;
	char	*value;
}	t_var;

const t_var variables[] = {
	{"VAR1", "111111"},
	{"VAR2", "222222"},
	{"START", "*"}
};

char	*expand_environment(char *str, int i)
{
	char	*ptr;
	size_t	len;

	if (!*ptr)
	{
		ptr = malloc(i + 1);
		if (!ptr)
			return (NULL);
		ptr[i] = '\0';
		return (ptr);
	}
	if (*ptr == '$')
	{
		ptr = ++str; // skip $
		while (isalnum(*ptr))
			ptr++;
		len = ptr - str;

		int j = 0;
		while (j < sizeof(variables)/sizeof(*variables))
		{
			if (strncmp(str, variables[j].name, len) == 0)
			{
				str = variables[j].value;
				break;
			}
			j++;
		}
		len = strlen(str);
	}
	else
	{
		ptr = str;
		while (*ptr && *ptr != '$')
		{
			if (*ptr == '\'')
			{
				ptr = strchr(++ptr, '\'');
				if (!ptr)
					return (NULL);
			}
			ptr++;
		}
		len = ptr - str;
	}
	ptr = expand_environment(ptr, i + len);
	memcpy(ptr + i, str, len);
	return (ptr);
}

void	remove_quotes(char *s, char **a2)
{
	char	*p;
	char	quot;

	*a2 = NULL;

	p = s;
	quot = '\0';
	while (*s)
	{
		if (quot && *s == quot)
		{
			quot = '\0';
			s++;
		}
		else if (!quot && (*s == '\"' || *s == '\''))
		{
			quot = *s;
			s++;
		}
		if (*s == '\0')
			break;
		if (!quot && *s == '*')
			*a2 = p;
		*p = *s;
		s++;
		p++;
	}
	*p = '\0';
}

char	**str_expander(char *str)
{
	char	*a2;
	char	**ret;

	str = expand_environment(str, 0);
	printf("str: %s\n", str);
	remove_quotes(str, &a2);
	printf("waildcard: %s\n", a2);
	printf("pattern: %s\n", str);
	if (a2 && 0) // stop now
		return (NULL); // run waildcard expander
	else
	{
		ret = calloc(2, sizeof(char *));
		if (ret)
			*ret = str;
		else
			free(str);
		return (ret);
	}
}

int main(int argc, char **argv)
{
	str_expander("\"'\"");
}