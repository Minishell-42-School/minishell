/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/16 12:47:17 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_heredoc(t_redirections *redir)
{
	printf("=D\n");

	int	fd;

	fd = open(redir->filename, O_RDONLY);
	close(fd);

	// int	heredoc_fd[2];
	// int	orig_fd;
	
	// if (pipe(heredoc_fd) == -1)
	// 	return ((void)printf("Error pipe\n"));
	// if (control_fd != -1)
	// {
	// 	dup2(control_fd, STDIN_FILENO);
	// 	close(control_fd);
	// }
	// if (cmd->next)
	// {
	// 	close(fd[0]);
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[1]);
	// }

	// -----------------

// void handle_heredoc(const char *delimiter, int *read_fd)
// {
//     int pipe_fds[2];
//     pipe(pipe_fds);  // pipe_fds[0] -> read end, pipe_fds[1] -> write end

//     char *line = NULL;
//     size_t len = 0;

//     while (1)
//     {
//         write(1, "> ", 2);  // prompt
//         ssize_t read = getline(&line, &len, stdin);
//         if (read == -1)
//             break;

//         // Remove newline se tiver
//         if (line[read - 1] == '\n')
//             line[read - 1] = '\0';

//         if (strcmp(line, delimiter) == 0)
//             break;

//         write(pipe_fds[1], line, strlen(line));
//         write(pipe_fds[1], "\n", 1);  // Adiciona newline de volta
//     }

//     free(line);
//     close(pipe_fds[1]);      // Fecha write end (importante!)
//     *read_fd = pipe_fds[0];  // Retorna o read end para ser redirecionado no filho
// }

}

void	definy_fd(t_command *cmd)
{
	t_redirections	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		while (redir->next && ((redir->type == R_IN && \
			redir->next->type == R_IN) || \
			((redir->type == R_OUT || redir->type == R_APPEND) && \
			(redir->next->type == R_OUT || redir->next->type == R_APPEND))))
		{
			handle_creat(redir);
			redir = redir->next;
		}
		if (redir->type == R_OUT || redir->type == R_APPEND)
			handle_out(redir);
		else if (redir->type == R_IN)
			handle_in(redir);
		else
			handle_heredoc(redir);
		redir = redir->next;
	}
}

static void	child_proc(t_command *cmd)
{
	char	*path;

	definy_fd(cmd);
	path = get_path(cmd);
	if (!path)
	{
		perror("get_path");
		exit(EXIT_FAILURE);
	}
	execve(path, cmd->args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	exec_redir(t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ((void)printf("Error at fork\n"));
	if (pid == 0)
		child_proc(cmd);
	else
		wait(NULL);
}
