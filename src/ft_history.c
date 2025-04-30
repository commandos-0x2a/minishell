/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:31:39 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/04/30 13:16:38 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <ctype.h>
#include <libft.h>

#define HISTORY_SIZE 100

enum	e_history
{
	SEEK_PREV = 0x0,
	SEEK_NEXT,
	SEEK_HEAD,
	SEEK_TAIL,

	ACTION_GET = 0x20,
	ACTION_SET,
	ACTION_CLEAR,

	TYPE_MASK = 0xf0,
	TYPE_SEEK = 0x0,
	TYPE_ADD = 0x10,
	TYPE_ACTION = 0x20,
};

typedef struct s_history
{
	char				*line;
	struct s_history	*prev;
	struct s_history	*next;
}	t_history;

static int history_seek(t_history **history_r, int op, char **line_r)
{
	if (op == SEEK_PREV)
	{
		if ((*history_r) && (*history_r)->prev)
			*history_r = (*history_r)->prev;
	}
	else if (op == SEEK_NEXT)
	{
		if ((*history_r) && (*history_r)->next)
			*history_r = (*history_r)->next;
	}
	else if (op == SEEK_HEAD)
	{
		while ((*history_r) && (*history_r)->prev)
			*history_r = (*history_r)->prev;
	}
	else if (op == SEEK_TAIL)
	{
		while ((*history_r) && (*history_r)->next)
			*history_r = (*history_r)->next;
	}
	if (line_r && *history_r)
		*line_r = (*history_r)->line;
	return (0);
}

static int	history_add_line(t_history **history_r, char **line_r)
{
	t_history	*cur;

	cur = ft_calloc(1, sizeof(t_history));
	if (!cur)
		return (-1);
	cur->line = ft_strdup(*line_r);
	if (!cur->line)
	{
		free(cur);
		return (-1);
	}
	history_seek(history_r, SEEK_HEAD, history_r);
	cur->next = *history_r;
	if (*history_r)
		(*history_r)->prev = cur;
	*history_r = cur;
	return (0);
}

static int	history_clear(t_history **history_r)
{
	t_history	*next;

	history_seek(history_r, SEEK_HEAD, history_r);
	while (*history_r)
	{
		next = (*history_r)->next;
		free((*history_r)->line);
		free(*history_r);
		(*history_r)->next = next;
	}
	
}

static int	history_action(t_history **history_r, int op, char **line_r)
{
	if (op == ACTION_GET)
	{
		if (*history_r)
			*line_r = (*history_r)->line;
	}
	else if (op == ACTION_SET)
		return (history_add_line(history_r, line_r));
	else if (op == ACTION_CLEAR)
		history_clear(history_r);
	return (0);
}

static int history_ctl(int op, ...)
{
	static t_history	*history;
	static size_t		size;
	va_list				ap;
	int					err;
	char				**line_r;

	va_start(ap, op);
	if ((op & TYPE_MASK) == TYPE_SEEK)
		err = history_seek(&history, op, va_arg(ap, char **));
	else if ((op & TYPE_MASK) == TYPE_ACTION)
		err = history_action(history, op, va_arg(ap, char **));
	else
		return (1);
	va_end(ap);
	return (err);
}






const char *history_move_up(void)
{
	const char	*line;

	history_ctl(ACTION_GET, &line);
	history_ctl(SEEK_NEXT, NULL);
	return (line);
}

const char *history_move_down(void)
{
	const char	*line;

	history_ctl(SEEK_PREV, NULL);
	history_ctl(SEEK_PREV, NULL);
	history_ctl(ACTION_GET, &line);
	return (line);
}

int	ft_add_history(const char *line)
{
	return (history_ctl(ACTION_SET, &line));
}

void	ft_clear_history(void)
{
	history_ctl(ACTION_CLEAR);
}
