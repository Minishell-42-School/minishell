/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:55:17 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/03 18:14:58 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_child_proc(t_shell *shell)
{
	char	*path;

	if (shell->cmd->redirs)
	{
		if (definy_fd(shell->cmd))
			exit(EXIT_FAILURE);
	}
	if (shell->last_status == 130)
		exit(130);
	path = get_path(shell, shell->cmd);
	if (!path)
		exit(EXIT_FAILURE);
	if (execve(path, shell->cmd->args, shell->new_envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

// #include <unistd.h>
// #include <string.h>

// // Escreve uma string no fd indicado
// void	ft_putstr_fd(char *s, int fd)
// {
// 	write(fd, s, strlen(s));
// }

// // Imprime a mensagem de erro no stderr (fd 2) com formato "cmd: msg\n"
// void	print_error(char *cmd, char *msg)
// {
// 	ft_putstr_fd(cmd, 2);
// 	ft_putstr_fd(": ", 2);
// 	ft_putstr_fd(msg, 2);
// 	ft_putstr_fd("\n", 2);
// }

// if (!path)
// {
// 	print_error(shell->cmd->command_name, "command not found");
// 	exit(127);
// }

// if (execve(path, shell->cmd->args, shell->new_envp) == -1)
// {
// 	if (errno == ENOENT)
// 	{
// 		print_error(shell->cmd->command_name, "command not found");
// 		exit(127);
// 	}
// 	else if (errno == EACCES)
// 	{
// 		print_error(shell->cmd->command_name, "Permission denied");
// 		exit(126);
// 	}
// 	else if (errno == EISDIR)
// 	{
// 		print_error(shell->cmd->command_name, "Is a directory");
// 		exit(126);
// 	}
// 	else
// 	{
// 		// Se quiser pode usar perror aqui para erros genéricos
// 		perror(shell->cmd->command_name);
// 		exit(EXIT_FAILURE);
// 	}
// }


// static void exec_child_proc(t_shell *shell)
// {
//     char *path;

//     if (shell->cmd->redirs)
//     {
//         if (definy_fd(shell->cmd))
//             exit(EXIT_FAILURE);
//     }
//     if (shell->last_status == 130)
//         exit(130);

//     path = get_path(shell, shell->cmd);
//     if (!path)
//     {
//         fprintf(stderr, "%s: command not found\n", shell->cmd->command_name);
//         exit(127);
//     }

//     if (execve(path, shell->cmd->args, shell->new_envp) == -1)
//     {
//         if (errno == ENOENT)
//             fprintf(stderr, "%s: command not found\n", shell->cmd->command_name);
//         else if (errno == EACCES)
//             fprintf(stderr, "%s: Permission denied\n", shell->cmd->command_name);
//         else if (errno == EISDIR)
//             fprintf(stderr, "%s: Is a directory\n", shell->cmd->command_name);
//         else
//             perror(shell->cmd->command_name);

//         if (errno == EACCES)
//             exit(126);
//         else if (errno == ENOENT)
//             exit(127);
//         else
//             exit(EXIT_FAILURE);
//     }
//     exit(EXIT_SUCCESS);
// }


static void	exec_parent_proc(t_shell *shell, pid_t pid)
{
	int	status;

	ign_signals();
	waitpid(pid, &status, 0);
	config_signals();
	if (WIFSIGNALED(status))
		shell->last_status = 128 + WTERMSIG(status);
	else
		shell->last_status = WEXITSTATUS(status);
}

void	exec_simple_cmd(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		exec_child_proc(shell);
	else
		exec_parent_proc(shell, pid);
}
