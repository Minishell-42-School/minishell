/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:13:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/12 13:46:38 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	print_error(char *cmd, char *msg)
// {
// 	ft_putstr_fd(cmd, 2);
// 	ft_putstr_fd(": ", 2);
// 	ft_putstr_fd(msg, 2);
// 	ft_putstr_fd("\n", 2);
// }

void	handle_error(t_shell *shell, t_command *cmd)
{
	if (errno == ENOENT)
		ft_printf_stderr("%s: %s\n", cmd->command_name, "command not found");
	else if (errno == EACCES)
		ft_printf_stderr("%s: %s\n", cmd->command_name, "Permission denied");
	else if (errno == EISDIR)
		ft_printf_stderr("%s: %s\n", cmd->command_name, "Is a directory");
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
		ft_printf_stderr("%s: %s\n", cmd->command_name, "command not found");
		free_all(shell, 127);
	}
	if (stat(path, &st) != 0)
	{
		ft_printf_stderr("%s: %s\n", path, "No such file or directory");
		free_all(shell, 127);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_printf_stderr("%s: %s\n", path, "Is a directory");
		free_all(shell, 126);
	}
	if (access(path, X_OK) != 0)
	{
		ft_printf_stderr("%s: %s\n", path, "Permission denied");
		free_all(shell, 126);
	}
}


// void	print_error(char *cmd, char *msg)
// {
// 	ft_putstr_fd(cmd, 2);
// 	ft_putstr_fd(": ", 2);
// 	ft_putstr_fd(msg, 2);
// 	ft_putstr_fd("\n", 2);
// }

// void	handle_error(t_shell *shell, t_command *cmd)
// {
// 	if (errno == ENOENT)
// 		print_error(cmd->command_name, "command not found");
// 	else if (errno == EACCES)
// 		print_error(cmd->command_name, "Permission denied");
// 	else if (errno == EISDIR)
// 		print_error(cmd->command_name, "Is a directory");
// 	else
// 		perror(cmd->command_name);
// 	if (errno == EACCES || errno == EISDIR)
// 		free_all(shell, 126);
// 	else if (errno == ENOENT)
// 		free_all(shell, 127);
// 	else
// 		free_all(shell, EXIT_FAILURE);
// }

// void	check_error(char *path, t_command *cmd, t_shell *shell)
// {
// 	struct stat	st;

// 	if (!path)
// 	{
// 		print_error(cmd->command_name, "command not found");
// 		free_all(shell, 127);
// 	}
// 	if (stat(path, &st) != 0)
// 	{
// 		print_error(path, "No such file or directory");
// 		free_all(shell, 127);
// 	}
// 	if (S_ISDIR(st.st_mode))
// 	{
// 		print_error(path, "Is a directory");
// 		free_all(shell, 126);
// 	}
// 	if (access(path, X_OK) != 0)
// 	{
// 		print_error(path, "Permission denied");
// 		free_all(shell, 126);
// 	}
// }