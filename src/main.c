#include "minishell.h"
#include <unistd.h>
#include <stdio.h>


void	exec_command(char **argv)
{
	int		i;
	int		fd;
	char	*outfile;
	char	full_path[PATH_MAX];
	extern char	**environ;

	i = 0;
	while (argv[i])
	{
		fd = -2;
		if (ft_strncmp(argv[i], ">>", 2) == 0)
		{
			if (ft_strlen(argv[i]) == 2)
				outfile = argv[++i];
			else
				outfile = argv[i] + 2;
			fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			argv[i - 1] = NULL;
			argv[i] = NULL;
		}
		else if (ft_strncmp(argv[i], ">", 1) == 0)
		{
			if (ft_strlen(argv[i]) == 1)
				outfile = argv[++i];
			else
				outfile = argv[i] + 1;
			fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			argv[i - 1] = NULL;
			argv[i] = NULL;
		}
		else if (ft_strcmp(argv[i], "|") == 0)
		{
			argv[i] = NULL;
			break ;
		}
		if (fd != -2)
		{
			if (fd == -1)
			{
				perror(outfile);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		i++;
	}
	get_full_path(full_path, argv, "");
	execve(full_path, argv, (char **){environ});
	exit(1);
}


int	executioner(char *line, int indent)
{
	char	**argv;
	int		i;
	int		pid;
	int		status;

	pid = fork();
	if (pid != 0)
	{
		waitpid(pid, &status, 0);
		return (status);
	}



	argv = tokenizer(line, 0);
	if (!argv)
		return 0;
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '(')
		{
			argv[i][ft_strlen(argv[i]) - 1] = '\0';
			tokenizer(argv[i] + 1, indent + 4);
		}
		else
		{
			if (ft_strcmp(argv[i], "&&") == 0)
				fprintf(stderr, "%-*s%i: AND\n", indent, "", i);
			else if (ft_strcmp(argv[i], "||") == 0)
				fprintf(stderr, "%-*s%i: OR\n", indent, "", i);
			else if (ft_strncmp(argv[i], "<<", 2) == 0)
			{
				char *limiter;
				if (ft_strlen(argv[i]) == 2)
					limiter = argv[++i];
				else
					limiter = argv[i] + 2;
				fprintf(stderr, "%-*sHEREDOC (%s)\n", indent, "", limiter);

			}
			else if (ft_strncmp(argv[i], "<", 1) == 0)
			{
				char *infile;
				if (ft_strlen(argv[i]) == 1)
					infile = argv[++i];
				else
					infile = argv[i] + 1;
				int fd = open(infile, O_RDONLY);
				if (fd == -1)
					perror("minishell");
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			else
			{
				exec_command(argv + i);
				printf("%-*s%i: %s\n", indent, "", i, argv[i]);
			}
		}
		i++;
	}
	exit(1);
}

int main(void)
{
    char    *line;

    // atexit(cleanup_shell);
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
            executioner(line, 0);
        free(line);
    }
    return (0);
}
