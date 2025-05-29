

#include "../../../includes/minishell.h"

// int	g_exit_signal = 0;

char	*gnl(int fd)
{
	char	*line = NULL;
	// int		bufsize = 0;
	int		len;

	write(1, "Heredoc ~> ", 11);
	line = get_next_line(fd);
	len = ft_strlen(line);
	if (len == -1)
	{
		free(line);
		return (NULL);
	}
	// remove newline
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	return line;
}


void loop_heredoc(t_redirections *redir, int fd)
{
	char *line;

	while (1)
	{
		line = gnl(fd);
		if (!line)
		{
			printf("%s\n", SIG_HEREDOC);
			line = malloc(1 * sizeof(char));
			line[0] = '\0';
		}
		if (ft_strncmp(line, redir->filename, ft_strlen(redir->filename)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		if (line[0] != '\0')
			write(fd, "\n", 1);
		free(line);
	}
}


// void	loop_heredoc(t_redirections *redir, int fd)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("Heredoc ~> ");
// 		if (!line)
// 		{
// 			printf("%s\n", SIG_HEREDOC);
// 			line = malloc(1 * sizeof(char));
// 			line[0] = '\0';
// 		}
// 		if (ft_strncmp(line, redir->filename, ft_strlen(redir->filename)) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(fd, line, ft_strlen(line));
// 		if (line[0] != '\0')
// 			write(fd, "\n", 1);
// 		free(line);
// 	}
// }

// static void	hdoc_sig(int sig)
// {
// 	(void)sig;
// 	printf("\n");
// 	// g_exit_signal = 130;
// 	exit(130);
// }

static void	hdoc_child_proc(t_redirections *redir, int hdo_fd[2])
{
	signal(SIGINT, SIG_DFL);
	// g_exit_signal = 0;
	close(hdo_fd[0]);
	loop_heredoc(redir, hdo_fd[1]);
	close(hdo_fd[1]);
	// exit(0);
}

// static void	hdoc_parent_proc(t_redirections *redir, int hdo_fd[2])
// {
// 	int status;

// 	close(hdo_fd[1]);
// 	waitpid(pid, &status, 0);
// 	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// 	{
// 		close(hdo_fd[0]);
// 		write(STDERR_FILENO, "\n", 1);
// 		exit(130);
// 	}
// 	if (dup2(hdo_fd[0], STDIN_FILENO) == -1)
// 		perror("dup2");
// 	close(hdo_fd[0]);
// }

void	handle_heredoc(t_redirections *redir)
{
	int		heredoc_fd[2];
	pid_t	pid;
	// int		orig_signal;
	int		status;

	// orig_signal = g_exit_signal;
	// g_exit_signal = 1;
	if (pipe(heredoc_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	rl_clear_history();
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		// g_exit_signal = orig_signal;
		return ;
	}
	if (pid == 0)
		hdoc_child_proc(redir, heredoc_fd);
	else
	{
		// int	old_stdin = dup(STDIN_FILENO);
		close(heredoc_fd[1]);
		// signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		// signal(SIGINT, handle_sigint);

		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(heredoc_fd[0]);
			g_exit_signal = 130;
			// WEXITSTATUS(status);
			return ;
			// write(STDERR_FILENO, "\n", 1);
			// exit(130);
		}
		// else
		// {
		// 	g_exit_signal = orig_signal;
		// 	if (g_exit_signal == 1)
		// 		g_exit_signal = 0;
		// }
		if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
			perror("dup2");
		// dup2(old_stdin, STDIN_FILENO);
		close(heredoc_fd[0]);
	}
}
