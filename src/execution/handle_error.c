/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:13:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/04 15:29:55 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *cmd, char *msg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	handle_error(t_command *cmd)
{
	if (errno == ENOENT)
		print_error(cmd->command_name, "command not found");
	else if (errno == EACCES)
		print_error(cmd->command_name, "Permission denied");
	else if (errno == EISDIR)
		print_error(cmd->command_name, "Is a directory");
	else
		perror(cmd->command_name);
	if (errno == EACCES || errno == EISDIR)
		exit(126);
	else if (errno == ENOENT)
		exit(127);
	else
		exit(EXIT_FAILURE);
}

void	check_error(char *path, t_command *cmd)
{
	struct stat	st;

	if (!path)
	{
		print_error(cmd->command_name, "command not found");
		exit(127);
	}
	if (stat(path, &st) != 0)
	{
		print_error(path, "No such file or directory");
		exit(127);
	}
	if (S_ISDIR(st.st_mode))
	{
		print_error(path, "Is a directory");
		exit(126);
	}
	if (access(path, X_OK) != 0)
	{
		print_error(path, "Permission denied");
		exit(126);
	}
}
