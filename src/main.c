#include "minishell.h"
#include <unistd.h>
#include <stdio.h>


void	exec_command(char **argv)
{
	char	full_path[PATH_MAX];
	extern char	**environ;
	int		i;
	int		fd;
	char	*outfile;

	if (!argv || !argv[0])
		exit(1);

	// Handle redirections first
	i = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], ">>", 2) == 0)
		{
			if (ft_strlen(argv[i]) == 2)
				outfile = argv[++i];
			else
				outfile = argv[i++] + 2;
			fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("minishell");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			argv[i - 1] = NULL;
			break;
		}
		else if (ft_strncmp(argv[i], ">", 1) == 0)
		{
			if (ft_strlen(argv[i]) == 1)
				outfile = argv[++i];
			else
				outfile = argv[i++] + 1;
			fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("minishell");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			argv[i - 1] = NULL;
			break;
		}
		i++;
	}

	// Handle quotes for remaining arguments
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '\'' || argv[i][0] == '\"')
		{
			size_t len = ft_strlen(argv[i]);
			if (len >= 2 && argv[i][len - 1] == argv[i][0])
			{
				// Move content one character left to remove opening quote
				ft_memmove(argv[i], argv[i] + 1, len - 2);
				argv[i][len - 2] = '\0';
			}
		}
		i++;
	}

	// First try direct execution (for absolute paths or ./command)
	if (argv[0][0] == '/' || (argv[0][0] == '.' && argv[0][1] == '/'))
	{
		if (access(argv[0], X_OK) == 0)
		{
			execve(argv[0], argv, environ);
			perror("minishell");
			exit(126);
		}
	}
	
	// Then try PATH lookup
	if (get_full_path(full_path, argv, "") == 0)
	{
		execve(full_path, argv, environ);
		perror("minishell");
	}
	exit(127);
}


int	executioner(char *line, int indent)
{
	char	**argv;
	int		i;
	int		pid;
	int		status;
	int		fd;

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
				pid_t proc = run_here_doc_process(limiter, &fd);
				if (proc == -1)
				{
					perror("minishell");
					exit(1);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			else if (ft_strncmp(argv[i], "<", 1) == 0)
			{
				char *infile;
				if (ft_strlen(argv[i]) == 1)
					infile = argv[++i];
				else
					infile = argv[i] + 1;
				fd = open(infile, O_RDONLY);
				if (fd == -1)
					perror("minishell");
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			else
			{
				exec_command(argv + i);
				fprintf(stderr, "%-*s%i: %s\n", indent, "", i, argv[i]);
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
