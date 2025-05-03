/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:09:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/05/03 13:35:29 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	mini_clean(t_mini *mini)
{
	if (mini->tokens)
		lst_clean(&mini->tokens);
	if (mini->env)
		lst_clean(&mini->env);
}

void	exit_handler(t_mini *mini, int exit_status)
{
	mini_clean(mini);
	if (g_sig != 0)
		exit(128 + g_sig);
	exit(exit_status);
}

char	*read_prompt(void)
{
	char	prompt[PATH_MAX + 3];
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		ft_strlcpy(cwd, "~", sizeof(cwd));
	cwd[PATH_MAX - 1] = '\0';
	ft_snprintf(prompt, PATH_MAX + 3, "%s$ ", cwd);
	return (readline(prompt));
}

int	start(t_mini *mini, char tty_path[PATH_MAX])
{
	char	*line;

	if (restore_tty(tty_path) == -1)
		return (1);
	setup_prompt_signal();
	line = read_prompt();
	setup_default_signal();
	if (!line)
	{
		ft_printf("\nexit\n");
		return (0);
	}
	if (!*line)
		return (1);
	add_history(line);
	mini->tokens = tokenizer(line);
	free(line);
	if (!mini->tokens)
		return (0);
	if (mini->tokens == (void *)0x1)
		return (1);
	if (check_syntax(mini->tokens) && flow_control(mini) == -1)
		return (-1);
	lst_clean(&mini->tokens);
	return (1);
}

int	main(int argc, char **argv)
{
	t_mini		mini;
	char		tty_path[PATH_MAX];
	int			loop;
	
	ft_bzero(&mini, sizeof(t_mini));
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		ft_fprintf(2, PREFIX"not a tty\n");
		return (1);
	}
	if (ft_ttyname_r(0, tty_path, sizeof(tty_path)) != 0)
		return (1);
	mini.argc = argc;
	mini.argv = argv;
	mini.env = copy_env_variables();
	if (!mini.env)
		return (1);
	g_sig = 0;
	loop = 1;
	while (loop == 1)
	{
		loop = start(&mini, tty_path);
		mini.tokens = NULL;
	}
	mini_clean(&mini);
	return (-loop);
}
