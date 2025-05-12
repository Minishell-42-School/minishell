/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/12 17:59:02 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	child_proc(t_command *cmd)
{
	int	fd;
	char	*path;
	// int	fd_backup;
	// if (!cmd->redirs->next) // Apenas 1 redir
	// {
	if (cmd->redirs->type == R_OUT) // >
	{
		fd = open(cmd->redirs->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			printf("Error for open the file");
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
	path = get_path(cmd);
	execve(path, cmd->args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
			
			// if (cmd->redirs->type == R_IN) // <
		// else if (cmd->redirs->type == R_DELIMITER) // <<
		// else // >>
	// }
}

void	exec_redir(t_command *cmd)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return ((void)printf("Error at fork\n"));
	if (pid == 0)
		child_proc(cmd);
	else
		wait(NULL);
}

