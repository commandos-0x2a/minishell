NAME		= minishell

CC			= cc
LDFLAGS		= -L./libft -lft -lreadline -lncurses
CFLAGS		= -Wall -Wextra -Werror -g
CPPFLAGS	= -I./libft/include -I./include

SRCDIR = src
OBJDIR = build

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG
endif

FILES = 	main					\
			tokenizer				\
			ft_readline				\
			\
			builtins/builtins		\
			builtins/cd				\
			builtins/echo			\
			builtins/env			\
			builtins/exit			\
			builtins/export			\
			builtins/pwd			\
			builtins/unset			\
			\
			utils/dptr				\
			utils/ft_getenv			\
			utils/get_full_path		\
			utils/ft_list			\
			utils/print_error		\
			utils/tty				\
			utils/signals			\
			utils/get_argv			\
			utils/check_syntax		\
			\
			expand/expand_line		\
			expand/expand_env		\
			expand/expand_str		\
			expand/expand_wildcard	\
			expand/match_pattern	\
			expand/expand_tokens	\
			\
 			execute/pipeline_control		\
 			execute/flow_control			\
			execute/execute_complex_command	\
			execute/execute_simple_command	\
			execute/redirection_handler		\
			execute/subshell				\
			execute/heredoc					\
			execute/wait_children			\
			\

#

OBJECTS = $(FILES:%=$(OBJDIR)/%.o)

all: libft $(NAME)

bonus: libft $(NAME)

libft:
	@$(MAKE) -C libft

$(NAME): $(OBJECTS) libft/libft.a
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
#	$(MAKE) -C libft clean
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all libft clean fclean re
