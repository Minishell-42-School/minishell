/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:15:39 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/05 11:43:03 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"
#include "pipe.h"

void	exec_pipeline(t_command *cmd)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	char	*path;

	prev_fd = -1;
	if (cmd->next && pipe(fd) == -1)
	{
		printf("Error at pipe\n");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		printf("Error at fork\n");
		return ;
	}

	if (pid == 0)
	{
		// Child 1
		path = get_path(cmd);
		// printf("Exec 1 - %s, %s\n", cmd->command_name, cmd->args[1]);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(path, cmd->args, NULL);
		free(path);
	}
	else
	{
		// Main
		pid = fork();
		if (pid == -1)
		{
			printf("Error at fork\n");
			return ;
		}
		if (pid == 0)
		{
			// Child 2
			path = get_path(cmd->next);
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			// printf("Exec 2- %s, %s\n", cmd->next->command_name, cmd->next->args[1]);
			execve(path, cmd->next->args, NULL);
			free(path);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			wait(NULL);
			wait(NULL);
			// free(path);
		}
	}
}


// prev_fd = -1;
// for (cada comando atual cmd em uma lista encadeada) {
//     if (não é o último comando)
//         pipe(fd);
    
//     pid = fork();
//     if (pid == 0) {
//         if (prev_fd != -1) {
//             dup2(prev_fd, STDIN_FILENO);
//             close(prev_fd);
//         }
//         if (não é o último comando) {
//             close(fd[0]); // fecha o lado de leitura
//             dup2(fd[1], STDOUT_FILENO);
//             close(fd[1]);
//         }
//         execve(...);
//     } else {
//         if (prev_fd != -1)
//             close(prev_fd);
//         if (não é o último comando) {
//             close(fd[1]); // fecha o lado de escrita
//             prev_fd = fd[0]; // guarda o read end para o próximo comando
//         }
//     }
// }
// wait por todos os processos filhos
