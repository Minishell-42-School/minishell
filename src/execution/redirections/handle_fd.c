/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:11:53 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/14 18:12:13 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_out(t_redirections *redir)
{
	int	fd;

	if (redir->type == R_OUT) // >
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else // if (redir->type == R_APPEND) // >>
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error for open the file");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("Error - dup");
		close(fd);
		return ;
	}
	close(fd);
}

void	handle_in(t_redirections *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY); // <
	if (fd == -1)
	{
		perror("Error for open the file");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("Error - dup");
		close(fd);
		return ;
	}
	close(fd);
}

void	handle_creat(t_redirections *redir)
{
	int	fd;

	fd = open(redir->filename, O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Error for open the file");
		return ;
	}
	close(fd);
}
