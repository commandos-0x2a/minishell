NAME	= minishell

# Compiler settings
CC			= cc
LDFLAGS		= -L./libft -lft -lreadline -lncurses
INCLUDES	= -I./libft/include -I./include
CFLAGS		:= -Wall -Wextra -Werror -g $(INCLUDES)

SRC_DIR = src
BUILD_DIR = build

FILES = main				\
		ft_join_path		\
		ft_getenv			\
		ft_setenv			\
		tokenizer			\
		print_tokenizer		\
		get_full_path		\
		here_doc			\
		readline_handler	\
		builtins/cd		\
		builtins/builtins	\
		builtins/echo		\
		builtins/pwd		\
		builtins/env		\
		builtins/exit	\
		builtins/test

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
