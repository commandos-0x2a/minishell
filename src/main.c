#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    char    *line;
	int		is_test;

	is_test = 0;
    // atexit(cleanup_shell);
	if (argc == 2 && ft_strcmp(argv[1], "test") == 0)
		is_test = 1;
    while (1)
    {
        line = readline(get_prompt());
        if (!line)
        {
            printf("\nexit\n");
            break;
        }
        handle_line(line);
        if (*line)
		{
			if (is_test)
				print_tokenizer(line, 0);
			else
                executioner(line, 0);
		}
        free(line);
    }
    return (0);
}
