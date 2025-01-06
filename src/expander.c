/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:54:21 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/01/06 13:46:47 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

void	argv_expander_old(char **argv)
{
	int		i;
	size_t	len;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '\'' || argv[i][0] == '\"')
		{
			len = ft_strlen(argv[i]);
			if (len >= 2 && argv[i][len - 1] == argv[i][0])
			{
				argv[i][len - 1] = '\0';
				argv[i]++;
			}
		}
		i++;
	}
}








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

	ptr = str;
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
		++ptr;
		++str;
		while (isalnum(*ptr))
			ptr++;
		len = ptr - str;

		size_t j = 0;
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
	remove_quotes(str, &a2);
	// printf("waildcard: %s\n", a2);
	// printf("pattern: %s\n", str);
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

char	**argv_expander_handler(char **argv, int i)
{
	char	**expanded;
	char	**new_argv;
	int		nb;

	if (*argv == NULL)
		return (ft_calloc(i + 1, sizeof(char *)));
	expanded = str_expander(*argv);
	if (!expanded)
		return (NULL);
	nb = 0;
	while (expanded[nb])
		nb++;
	new_argv = argv_expander_handler(argv + 1, i + nb);
	if (!new_argv)
	{
		while (--nb >= 0)
			free(expanded[nb]);
		free(expanded);
		return (NULL);
	}
	while (--nb >= 0)
		new_argv[i + nb] = expanded[nb];
	free(expanded);
	return (new_argv);
}

char	**argv_expander(char **argv)
{
	return (argv_expander_handler(argv, 0));
}
