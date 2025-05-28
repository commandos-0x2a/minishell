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
# define MINISHELL_H

# define __USE_XOPEN2K8
# define _GNU_SOURCE

# include <libft.h>
# include <sys/wait.h>
# include <ft_printf.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# ifdef __linux__
#  include <linux/limits.h>
# else
#  include <limits.h>
# endif

# define PREFIX "minishell: "

enum	e_qouts
{
	SINGLE_QUOTE = 0x1,
	DOUBLE_QUOTE = 0x2
};

enum	e_is_pipe
{
	IS_NEXT_PIPE = 1,
	IS_PREV_PIPE = 2
};

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

typedef struct s_mini
{
	t_list	*tokens;
	t_list	*env;
	t_list	*heredoc_files;
	char	tty_path[PATH_MAX];
	int		argc;
	char	**argv;
	int		exit_status;
}	t_mini;

struct s_cmd
{
	char	**argv;
	char	**env;
	char	full_path[PATH_MAX];
	int		err;
};

extern volatile int	g_sig;

void	mini_clean(t_mini *mini);
void	exit_handler(t_mini *mini, int exit_status);
int		check_syntax(t_list *lst);
int		print_error(const char *file, int line);
int		print_file_error(const char *file, int line, const char *target);

/*  subshell  */
int		is_subshell(t_list *lst);
int		subshell_syntax(t_list *lst);
void	run_subshell(t_mini *mini);

/*  t_list  */
t_list	*lst_expand(t_list *lst, char **slices);
void	*lst_move2next(t_list **lst);
void	*lst_clean(t_list **lst);
char	**lst_2_argv(t_list **lst, int flcean);
char	**lst_2_dptr(t_list *lst);
void	lst_remove_one(t_list **lst, t_list *prev);

/*  tokenizer  */
t_list	*tokenizer(const char *s);
char	*get_argv0(t_list *lst);
void	get_argv(t_list **lst);

/*  expand  */
char	*expand_line(const char *s);
char	**expand_str(t_mini *mini, char *str);
char	*expand_env(t_mini *mini, char *str);
int		expand_tokens(t_mini *mini, t_list *lst);
t_list	*expand_tokens_2lst(t_mini *mini, const char *str);
void	replace_qouts(char *s);
char	*remove_qouts(char *str);

char	**expand_wildcard(char *pattern);
int		match_pattern(const char *pattern, const char *str, char qout);

/*  execution  */
int		flow_control(t_mini *mini);
int		pipeline_control(t_mini *mini);
int		execute_complex_command(t_mini *mini, int in_fd,
			int pipefds[2], int pipe_mask);
int		execute_simple_command(t_mini *mini);
int		get_full_path(t_list *env, char full_path[PATH_MAX], char *cmd);

/*  Wait children  */
int		wait_all_childrens(pid_t victim);
int		wait_one_child(pid_t victim);

/*  redirection handling  */
int		redirection_handler(t_mini *mini, int heredoc_fd);
int		heredoc_forever(t_mini *mini, t_list *lst);

/*  environment variables  */
t_list	*copy_env_variables(char **environ);
char	*ft_getenv(t_list *env, const char *name);

/*  built-in commands  */
int		handle_builtin(t_mini *mini, char **argv, int _exit);
int		is_builtin(t_mini *mini, const char *cmd, int expand);
int		ft_cd(t_mini *mini, char **argv);
int		ft_echo(char **argv);
int		ft_pwd(char **argv);
int		ft_env(t_mini *mini, char **argv);
int		ft_exit(char **argv, int *_exit);
int		ft_export(t_mini *mini, char **argv);
int		ft_unset(t_mini *mini, char **argv);

/*  signal handling functions  */
void	setup_prompt_signal(void);
void	setup_default_signal(void);
void	reset_signals(void);

/*  utils functions  */
int		ft_ttyname_r(int fd, char *buf, size_t len);
int		restore_tty(char tty_path[PATH_MAX]);
pid_t	ft_getpid(void);

char	**copy_dptr(char **dptr);
void	free_dptr(char **ptr);

#endif
