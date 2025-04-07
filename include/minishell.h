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
	struct s_list	*next;
	char			*token;
}	t_list;

void	*fclean_list(t_list **lst);
void	*clean_list(t_list **lst);

// Terminal configuration
char *get_prompt(void);
void handle_line(char *line);
void cleanup_shell(void);

/*  tokenizer  */
t_list		*tokenizer(char *s);

/*  argv  */
char		*get_argv0(t_list *lst);
void		get_argv(t_list **lst_p);
char		**lst_2_argv(t_list **lst, int i);

/*  expander  */
char	*expand_str(char *str);
char	*expand_str_no_quote(char *str);
char	**argv_expander(char **argv);
char	**argv_expander2(char **argv, int i);

# define IS_PIPE		0b01
# define IS_PREV_PIPE	0b10
# define IS_PIPE_MASK	0b11

/*  execution  */
int		execute_complex_command(t_list **lst, int *fd, int is_pipe);
int		pipeline_control(t_list **lst);
int		check_syntax(t_list *lst);
int		wait_children(int target_pid);
void	execute_simple_command(t_list **lst);

/*  Redirection handling  */
int	redirection_handler(t_list *lst, int heredoc_fd, int change_std);
int	heredoc_start_read(char *limiter, int out_fd);
int	heredoc_forever(t_list *lst);


/*  Built-in commands  */
int		handle_builtin(char **argv, int _exit);
int		is_builtin(char *cmd);
int		ft_cd(char **argv);
int		ft_echo(char **argv);
int		ft_pwd(char **argv);
int		ft_env(char **argv);
int		ft_exit(char **argv, int *_exit);
int		ft_test(char **argv);
int		ft_export(char **argv);
int		ft_unset(char **argv);

void setup_signals(void);
void reset_signals(void);

// Environment management functions
char ***__init__env(void);
char **create_env_copy(void);
void cleanup_env_copy(void);

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
