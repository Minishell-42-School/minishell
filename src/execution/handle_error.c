/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:13:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/12 16:08:48 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_error(t_shell *shell, t_command *cmd)
{
	if (errno == ENOENT)
		ft_printf_stderr("%s: command not found\n", cmd->command_name);
	else if (errno == EACCES)
		ft_printf_stderr("%s: Permission denied\n", cmd->command_name);
	else if (errno == EISDIR)
		ft_printf_stderr("%s: Is a directory\n", cmd->command_name);
	else
		perror(cmd->command_name);
	if (errno == EACCES || errno == EISDIR)
		free_all(shell, 126);
	else if (errno == ENOENT)
		free_all(shell, 127);
	else
		free_all(shell, EXIT_FAILURE);
}

void	check_error(char *path, t_command *cmd, t_shell *shell)
{
	struct stat	st;

	if (!path)
	{
		ft_printf_stderr("%s: command not found\n", cmd->command_name);
		free_all(shell, 127);
	}
	if (stat(path, &st) != 0)
	{
		ft_printf_stderr("%s: No such file or directory\n", path);
		free_all(shell, 127);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_printf_stderr("%s: Is a directory\n", path);
		free_all(shell, 126);
	}
	if (access(path, X_OK) != 0)
	{
		ft_printf_stderr("%s: Permission denied\n", path);
		free_all(shell, 126);
	}
}
