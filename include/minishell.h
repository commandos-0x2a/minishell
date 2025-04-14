/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:15:08 by yaltayeh          #+#    #+#             */
/*   Updated: 2025/03/21 12:35:02 by yaltayeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# define __USE_XOPEN2K8
# define _GNU_SOURCE // for WUNTRACED

#include <libft.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#ifdef __linux__
#include <linux/limits.h>
// #  include <bits/termios-c_lflag.h>
// #  include <asm-generic/termbits.h>
#include <bits/sigaction.h>
#include <asm-generic/signal-defs.h>
#else
#include <limits.h>
#endif

#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <termios.h>
#include <signal.h>

#include "minishell_utils.h"

#define PREFIX "minishell: "

#define HOSTNAME_MAX 64
#define USERNAME_MAX 32
#define PATH_MAX_LEN 3000
#define PROMPT_MAX (HOSTNAME_MAX + USERNAME_MAX + PATH_MAX_LEN + 10)

// Define maximum sizes for config values
#define MAX_PROMPT_STYLE 32
#define MAX_CONFIG_LINE 256

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

typedef struct s_mini
{
	t_list	*tokens;
	t_list	*env;
	int		exit_status;
}	t_mini;

extern int	g_status;

/*  tokenizer  */
char		*add_space_to_line(const char *s);
t_list	*tokenizer(char *s);
void		*lst_clean(t_list **lst);
void		*lst_move2next(t_list **lst);

/*  argv  */
int		get_full_path(t_list *env, char full_path[PATH_MAX], char *cmd);
char	*get_argv0(t_list *lst);
void	get_argv(t_list **lst);
char	**lst_2_dptr(t_list *lst);

/*  expander  */
char	*expand_str(t_list *env, char *str);
char	*expand_str_no_quote(t_list *env, char *str);
char	**argv_expander(t_list *env, char **argv);
char	**argv_expander2(t_list *env, char **argv, int i);

# define IS_PIPE		0b01
# define IS_PREV_PIPE	0b10
# define IS_PIPE_MASK	0b11

/*  execution  */
int		flow_control(t_mini *mini);
int		pipeline_control(t_mini *mini);
int		execute_complex_command(t_mini *mini, int *fd, int is_pipe);
void	execute_simple_command(t_mini *mini);
int		wait_children(int target_pid);
int		check_syntax(t_list *lst);

/*  Redirection handling  */
int	redirection_handler(t_list *lst, t_list *env, int heredoc_fd, int change_std);
int	heredoc_start_read(t_list *env, char *limiter, int out_fd);
int	heredoc_forever(t_list *lst, t_list *env);

/*  Environment variables  */
t_list	*copy_env_variables(void);
char	*ft_getenv(t_list *env, const char *name);


/*  Built-in commands  */
int		handle_builtin(t_mini *mini, char **argv, int _exit);
int		is_builtin(t_list *env, char *cmd);
int		ft_cd(t_mini *mini, char **argv);
int		ft_echo(char **argv);
int		ft_pwd(char **argv);
int		ft_env(t_mini *mini, char **argv);
int		ft_exit(char **argv, int *_exit);
int		ft_test(t_mini *mini, char **argv);
int		ft_export(t_mini *mini, char **argv);
int		ft_unset(t_mini *mini, char **argv);

void setup_signals(void);
void reset_signals(void);


// Add global variable declaration and new function prototypes
int *heredoc_active(void);

void save_signal_handlers(void);
void restore_signal_handlers(void);

// Add this struct and function prototype
struct s_sig_handlers
{
	struct sigaction old_int;
	struct sigaction old_quit;
};

struct s_sig_handlers *get_sig_handlers(void);


#endif
