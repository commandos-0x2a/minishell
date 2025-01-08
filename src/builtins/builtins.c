/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:57:28 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/08 09:26:33 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Regular built-ins can run in child process (output only)
* Shell built-ins must run in parent process (modify shell state)
*/
int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);

    if (ft_strcmp(cmd, "cd") == 0 \
		|| ft_strcmp(cmd, "exit") == 0 \
     	|| ft_strcmp(cmd, "export") == 0 \
        || ft_strcmp(cmd, "unset") == 0)
		return (1);
    if (ft_strcmp(cmd, "echo") == 0 ||
            ft_strcmp(cmd, "pwd") == 0 ||
            ft_strcmp(cmd, "env") == 0)
        return (2);
    return (0);
}

int handle_builtin(char **argv, int _exit)
{
	int	ret;

	if (!*argv)
		return (1);
	ret = 1;
	if (ft_strcmp(*argv, "cd") == 0)
		ret = ft_cd(argv);
	else if (ft_strcmp(*argv, "exit") == 0)
		ret = ft_exit(argv); 
	else if (ft_strcmp(*argv, "export") == 0)
		ret = 0; // add export function
	else if (ft_strcmp(*argv, "unset") == 0)
		ret = 0; // add export function
	else if (ft_strcmp(*argv, "echo") == 0)
		ret = ft_echo(argv); 
	else if (ft_strcmp(*argv, "pwd") == 0)
		ret = ft_pwd(argv); 
	else if (ft_strcmp(*argv, "env") == 0)
		ret = ft_env(argv);
	else
		return (1); // Impossible to get here but just in case
	if (_exit)
		exit(ret);
	return (ret);
}
