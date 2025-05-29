/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:55:17 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/22 13:11:57 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_external_cmd(t_command *cmd)
{
	char	*path;
	pid_t	pid;

	path = get_path(cmd);
	if (!path)
		return ;
	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd->args, __environ);
		perror("Error execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("Error fork");
	if (!ft_strchr(cmd->command_name, '/'))
		free(path);
}
