#include "minishell.h"

void	print_tokenizer(char *line, int indent)
{
	char	**argv;
	int		i;

	argv = tokenizer(line, 0);
	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '(')
			{
				argv[i][ft_strlen(argv[i]) - 1] = '\0';
				print_tokenizer(argv[i] + 1, indent + 4);
			}
		else
			printf("%-*s%i: %s\n", indent, "", i, argv[i]);
		i++;
	}
}
