NAME	= minishell

# Compiler settings
CC			= cc
LDFLAGS		= -L./libft -lft -lreadline -lncurses
INCLUDES	= -I./libft/include -I./include
CFLAGS		:= -Wall -Wextra -Werror -g $(INCLUDES)

SRC_DIR = src
BUILD_DIR = build

FILES = main					\
		ft_join_path			\
		ft_getenv				\
		ft_setenv				\
		get_full_path			\
		\
		readline_handler		\
		signals					\
		config					\
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

OBJECTS = $(FILES:%=$(BUILD_DIR)/%.o)

all: libft $(NAME)

bonus: libft $(NAME)

libft:
	@$(MAKE) -C libft

$(NAME): $(OBJECTS) libft/libft.a
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all bonus libft clean fclean re
