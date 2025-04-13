NAME		= minishell

CC			= cc
LDFLAGS		= -L./libft -lft -lreadline -lncurses
CFLAGS		= -Wall -Wextra -Werror -g
CPPFLAGS	= -I./libft/include -I./include

SRCDIR = src
OBJDIR = build

FILES = builtins/builtins			\
			builtins/cd				\
			builtins/echo			\
			builtins/env			\
			builtins/exit			\
			builtins/export			\
			builtins/pwd			\
			builtins/test			\
			builtins/unset			\
			utils/dptr				\
			utils/ft_getenv			\
			utils/ft_setenv			\
			utils/get_full_path		\
			utils/readline_handler	\
			utils/signals			\
			utils/list				\
			str_expander			\
			wait_children			\
			here_doc				\
			get_argv				\
			get_argv0				\
			add_space_to_line		\
 			execution/flow_control				\
 			execution/pipeline_control			\
			execution/execute_complex_command	\
			execution/execute_simple_command	\
			execution/redirection_handler		\
			main								\
			wildcard							\
			tokenizer							\
			check_syntax						\
			print_tokenizer						\
#


#

OBJECTS 			= $(FILES:%=$(OBJDIR)/%.o)

all: libft $(NAME)

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
