/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:19:27 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/24 15:17:53 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_and_exit(t_mdata *mdata, int exit_status)
{
	cleanup_env_copy();
	if (mdata)
	{
		if (mdata->command_pid)
			free(mdata->command_pid);
		if (mdata->line)
			free(mdata->line);
		if (mdata->tokens)
			free(mdata->tokens);	
	}
	exit(exit_status);
}