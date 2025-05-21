

#include "../../../includes/minishell.h"

void	loop_heredoc(t_redirections *redir, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("Heredoc ~> ");
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

static void	hdoc_child_proc(t_redirections *redir, int hdo_fd[2])
{
	signal(SIGINT, SIG_DFL);
	close(hdo_fd[0]);
	loop_heredoc(redir, hdo_fd[1]);
	close(hdo_fd[1]);
	exit(0);
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

	if (pipe(heredoc_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		hdoc_child_proc(redir, heredoc_fd);
	else
	{
		int status;
		close(heredoc_fd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(heredoc_fd[0]);
			write(STDERR_FILENO, "\n", 1);
			exit(130);
		}
		if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
			perror("dup2");
		close(heredoc_fd[0]);
	}
}
