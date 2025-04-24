/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:12:22 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/24 12:12:34 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_subshell(t_mini *mini)
{
	char	*argv0;
	size_t	line_len;
	char	*line;

	argv0 = get_argv0(mini->tokens);
	++argv0;
	line_len = ft_strlen(argv0);
	if (argv0[line_len - 1] != ')')
		exit_handler(mini, 1);
	argv0[line_len - 1] = '\0';
	line = ft_strdup(argv0);
	if (!line)
		exit_handler(mini, 1);
	lst_clean(&mini->tokens);
	mini->tokens = tokenizer(line);
	free(line);
	if (!mini->tokens)
		exit_handler(mini, 1);
	if (flow_control(mini) != 0)
	{
		perror("flow_control");
		exit_handler(mini, 1);
	}
	exit_handler(mini, 0);
}

int	is_subshell(t_list *lst)
{
	char	*argv0;

	argv0 = get_argv0(lst);
	if (!argv0)
		return (0);
	if (*argv0 == '(')
		return (1);
	return (0);
}

int	subshell_syntax(t_list *lst)
{
	if (lst->next || lst->next->str)
		return (0);
	return (1);
}
