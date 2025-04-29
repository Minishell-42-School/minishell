/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:15:39 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/29 18:04:56 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"
#include "pipe.h"

void	exec_pipeline(t_command *cmd)
{
	int	fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*path1;
	char	*path2;

	path1 = ft_strjoin("/bin/", cmd->command_name);
	path2 = ft_strjoin("/bin/", cmd->next->command_name);
	if (cmd->next && pipe(fd) == -1)
	{
		printf("Error at pipe\n");
		return ;
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		printf("Error at fork\n");
		return ;
	}
	
	if (pid1 == 0)
	{
		// Child 1
		printf("Exec 1 - %s, %s\n", cmd->command_name, cmd->args[1]);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(path1, cmd->args, NULL);
	}
	else
	{
		// Main
		pid2 = fork();
		if (pid2 == -1)
		{
			printf("Error at fork\n");
			return ;
		}
		if (pid2 == 0)
		{
			// Child 2
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			printf("Exec 2- %s, %s\n", cmd->next->command_name, cmd->next->args[1]);
			execve(path2, cmd->next->args, NULL);
		}
		else
		{
			printf("Proc pai\n");
			close(fd[0]);
			close(fd[1]);
			wait(NULL);
			wait(NULL);
			free(path1);
			free(path2);
		}
	}
}
