/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:59:26 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/28 00:54:39 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_subshell(char **argv)
{
	char	*line;
	t_mdata	mdata;
	int		status;

	if (argv[1] != NULL)
		exit(222);
	line = *argv;
	line[ft_strlen(line) - 1] = '\0';
	line++;
	line = ft_strdup(line);
	if (!line)
	{
		PRINT_ALLOCATE_ERROR;
		exit(1);
	}
	status = flow_control(&mdata);

	exit(status);
}

// allocate:
//	- char **argv
//	- char	**env # "global"
void	run_command(char **argv)
{
	char		full_path[PATH_MAX];
	int			err;
	char		**expand_argv;

	if (!*argv) // command not exist
		exit(0);
		
	// Check if the first character of the command is an opening parenthesis
	if ((*argv)[0] == '(')
		run_subshell(argv);
	
	expand_argv = argv_expander2(argv, 0);
	free_dptr(argv);
	argv = expand_argv;
	if (!argv)
	{
		PRINT_ALLOCATE_ERROR;
		exit(-1);
	}
	expand_argv = handle_wildcards(argv);
	free_dptr(argv);
	argv = expand_argv;
	if (!argv)
	{
		PRINT_ALLOCATE_ERROR;
		exit(-1);
	}
	
	// Check for built-in commands before getting full path and executing.
	if (is_builtin(argv[0]))
		handle_builtin(NULL, argv, 1);
	
	err = get_full_path(full_path, argv[0]);
	if (err == 0)
	{
		execve(full_path, argv, *__init__env());
		perror(PREFIX"execve");
		err = 1;
	}
	free_dptr(argv);
	cleanup_env_copy();
	exit(err);
}
