/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:00:00 by mkurkar           #+#    #+#             */
/*   Updated: 2025/04/14 06:07:41 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *s)
{
	if (!*s || (*s >= '0' && *s <= '9'))
		return (0);
	while (*s && *s != '=')
	{
		if (!(((*s >= 'a') && (*s <= 'z')) || \
				((*s >= 'A') && (*s <= 'Z')) || \
				((*s >= '0') && (*s <= '9')) || \
				*s == '_'))
			return (0);
		s++;
	}
	return (1);
}

static char	*make_env_variable(char *name, char *value)
{
	size_t	len;
	char	*new_env;

	len = ft_strlen(name);
	len++;
	len += ft_strlen(value);
	
	new_env = malloc(++len);
	if (!new_env)
		return (NULL);
	ft_strlcpy(new_env, name, len);
	ft_strlcat(new_env, "=", len);
	ft_strlcat(new_env, value, len);
	return (new_env);
}

static int	add_env_var(t_list **env, char *name, char *value)
{
	t_list	*prev;
	t_list	*cur;
	size_t	name_len;
	char	*new_env;
	
	prev = NULL;
	cur = *env;
	name_len = ft_strlen(name);
	while (cur && cur->str)
	{
		if (ft_strncmp(cur->str, name, name_len) == 0 && \
			cur->str[name_len] == '=')
			break ;
		prev = cur;
		cur = cur->next;
	}
	if (!cur)
	{
		if (!prev)
		{
			*env = ft_calloc(1, sizeof(t_list));
			if (!*env)
				return (1);
			cur = *env;
		}
		else
		{
			prev->next = ft_calloc(1, sizeof(t_list));
			if (!prev->next)
				return (1);
			cur = prev->next;
		}
	}
	new_env = make_env_variable(name, value);
	if (!new_env)
		return (1);
	if (cur->str)
		free(cur->str);
	cur->str = new_env;
	return (0);
}

int	ft_export(t_mini *mini, char **argv)
{
	int		i;
	char	*equals;
	t_list	*cur;
	
	if (!argv[1])
	{
		cur = mini->env;
		while (cur && cur->str)
		{
			ft_printf("declare -x %s\n", cur->str);
			cur = cur->next;
		}
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		equals = ft_strchr(argv[i], '=');
		if (equals)
		{
			*equals++ = '\0';
			if (!*equals)
				continue ;
			if (!is_valid_identifier(argv[i]))
			{
				ft_fprintf(2, PREFIX"export: not a valid identifier\n");
				return (1);
			}
			if (add_env_var(&mini->env, argv[i], equals))
			{
				PRINT_ALLOCATE_ERROR;
				return (1);
			}
		}
		i++;
	}
	return (0);
}
