/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:00:00 by mkurkar           #+#    #+#             */
/*   Updated: 2025/05/25 17:31:28 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *s)
{
	if (!*s || (*s >= '0' && *s <= '9'))
		return (0);
	while (*s && *s != '=')
	{
		if (!(((*s >= 'a') && (*s <= 'z'))
				|| ((*s >= 'A') && (*s <= 'Z'))
				|| ((*s >= '0') && (*s <= '9'))
				|| *s == '_'))
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
	if (value)
		len += ft_strlen(value);
	new_env = malloc(++len);
	if (!new_env)
		return (NULL);
	if (value)
		ft_snprintf(new_env, len, "%s=%s", name, value);
	else
		ft_snprintf(new_env, len, "%s", name);
	return (new_env);
}

static int	add_env_var(t_list **env, char *name, char *value)
{
	t_list	*cur;
	size_t	name_len;

	name_len = ft_strlen(name);
	if (!*env)
		*env = ft_calloc(1, sizeof(t_list));
	cur = *env;
	while (cur && cur->str)
	{
		if (ft_strncmp(cur->str, name, name_len) == 0
			&& (cur->str[name_len] == '=' || cur->str[name_len] == '\0'))
			break ;
		if (!cur->next)
			cur->next = ft_calloc(1, sizeof(t_list));
		cur = cur->next;
	}
	if (!cur)
		return (1);
	free(cur->str);
	cur->str = make_env_variable(name, value);
	if (!cur->str)
		return (1);
	return (0);
}

static int	update_env(t_list **env, char *identify)
{
	char	*equals;

	equals = ft_strchr(identify, '=');
	if (equals)
		*equals++ = '\0';
	if (!is_valid_identifier(identify))
	{
		ft_fprintf(2, PREFIX"export: not a valid identifier\n");
		return (1);
	}
	if (add_env_var(env, identify, equals))
	{
		print_error(__FILE__, __LINE__);
		return (1);
	}
	return (0);
}

int	ft_export(t_mini *mini, char **argv)
{
	int		i;
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
		if (update_env(&mini->env, argv[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
