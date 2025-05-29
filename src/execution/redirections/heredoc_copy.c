/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/29 12:50:59 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// static void	loop_heredoc(t_redirections *redir, int fd)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("Heredoc ~> ");
// 		if (!line)
// 		{
// 			printf("Warning: here-document delimited by end-of-file\n");
// 			free(line);
// 			break ;
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

// static void	hdoc_child_proc(t_redirections *redir, int hdo_fd[2])
// {
// 	close(hdo_fd[0]);
// 	heredoc_signals();
// 	loop_heredoc(redir, hdo_fd[1]);
// 	close(hdo_fd[1]);
// 	exit(EXIT_SUCCESS);
// }

// static void	hdoc_parent_proc(int hdo_fd[2], pid_t pid)
// {
// 	int	status;

// 	close(hdo_fd[1]);
// 	ign_signals();
// 	waitpid(pid, &status, 0);
// 	config_signals();
// 	if (WIFSIGNALED(status))
// 		g_exit_status = 128 + WTERMSIG(status);
// 	else
// 		g_exit_status = WEXITSTATUS(status);
// 	if (dup2(hdo_fd[0], STDIN_FILENO) == -1)
// 		perror("dup2");
// 	close(hdo_fd[0]);
// }

// void	handle_heredoc(t_redirections *redir)
// {
// 	int		heredoc_fd[2];
// 	pid_t	pid;

// 	if (pipe(heredoc_fd) == -1)
// 	{
// 		perror("pipe");
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		close(heredoc_fd[0]);
// 		close(heredoc_fd[1]);
// 		return ;
// 	}
// 	if (pid == 0)
// 		hdoc_child_proc(redir, heredoc_fd);
// 	else
// 		hdoc_parent_proc(heredoc_fd, pid);
// }