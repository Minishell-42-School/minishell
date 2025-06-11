/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/04 17:52:31 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_out(t_redirections *redir)
{
	int	fd;

	if (redir->type == R_OUT)
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redir->filename);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_in(t_redirections *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->filename);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_creat(t_redirections *redir)
{
	int	fd;

	fd = open(redir->filename, O_CREAT, 0644);
	if (fd == -1)
	{
		perror(redir->filename);
		return (1);
	}
	close(fd);
	return (0);
}

int	definy_fd(t_command *cmd)
{
	t_redirections	*redir;
	int				error_control;

	error_control = 0;
	redir = cmd->redirs;
	while (redir)
	{
		while (redir->next && \
			((redir->type == R_OUT || redir->type == R_APPEND) && \
			(redir->next->type == R_OUT || redir->next->type == R_APPEND)))
		{
			if (handle_creat(redir))
				return (1);
			redir = redir->next;
		}
		if (redir->type == R_OUT || redir->type == R_APPEND)
			error_control = handle_out(redir);
		else if (redir->type == R_IN)
			error_control = handle_in(redir);
		if (error_control)
			return (1);
		redir = redir->next;
	}
	return (0);
}
