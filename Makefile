NAME	= minishell

CC			= cc
LDFLAGS		= -L./libft -lft -lreadline -lncurses
CFLAGS		= -Wall -Wextra -Werror -g
CPPFLAGS	= -I./libft/include -I./include

SRCDIR = src
OBJDIR = build

FILES = main						\
		utils/ft_join_path			\
		utils/ft_getenv				\
		utils/ft_setenv				\
		utils/get_full_path			\
		\
		utils/readline_handler		\
		utils/signals				\
		utils/config				\
		utils/ft_free_array_str		\
		\
		expanders/str_expander	\
		expanders/wildcard		\
		\
		tokenizers/print_tokenizer		\
		tokenizers/tokenizer			\
		tokenizers/get_argv0			\
		tokenizers/get_argv				\
		\
		execution/flow_control			\
		execution/here_doc				\
		execution/pipeline_control		\
		execution/wait_children			\
		execution/command_execution		\
		execution/redirection_handler	\
		\
		builtins/cd			\
		builtins/builtins	\
		builtins/echo		\
		builtins/pwd		\
		builtins/env		\
		builtins/exit		\
		builtins/test 		\
		builtins/export		\
		builtins/unset		\
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
	$(MAKE) -C libft clean
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus libft clean fclean re
