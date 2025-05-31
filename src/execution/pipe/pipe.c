/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:15:39 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/29 12:50:22 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	exec_child_proc(t_command *cmd)
{
	char	*path;

	path = get_path(cmd);
	if (!path)
	{
		perror("get_path");
		exit(EXIT_FAILURE);
	}
	execve(path, cmd->args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	child_proc(t_command *cmd, int control_fd, int fd[2])
{
	if (control_fd != -1)
	{
		dup2(control_fd, STDIN_FILENO);
		close(control_fd);
	}
	if (cmd->next)
	{
		close(fd[0]);  // Fecha a leitura do pipe
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (cmd->redirs)
		definy_redir_fd(cmd);
	exec_child_proc(cmd);
}

static void	parent_proc(t_command *cmd, int *control_fd, int fd[2])
{
	if (*control_fd != -1)
		close(*control_fd);
	if (cmd->next)
	{
		close(fd[1]);      // Fecha a escrita no pipe
		*control_fd = fd[0];  // Próximo comando vai ler daqui
	}
	else
	{
		close(fd[0]);  // Último comando, não precisa mais do fd
	}
}

void	pipe_signal()
{
	int	status;
	pid_t pid;

	ign_signals();
	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		else
			g_exit_status = WEXITSTATUS(status);
	}
	config_signals();
}

void	exec_pipe(t_command *cmd)
{
	int		fd[2];
	int		control_fd;
	pid_t	pid;

	control_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
		{
			perror("pipe");
			return ;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
			child_proc(cmd, control_fd, fd);
		else
		{
			parent_proc(cmd, &control_fd, fd);
			cmd = cmd->next;
		}
	}
	pipe_signal();
}



// -------------------------------------------------

// static void	exec_child_proc(t_command *cmd)
// {
// 	char	*path;

// 	path = get_path(cmd);
// 	if (!path)
// 	{
// 		perror("get_path");
// 		exit(EXIT_FAILURE);
// 	}
// 	execve(path, cmd->args, NULL);
// 	perror("execve");
// 	exit(EXIT_FAILURE);
// }

// static void	child_proc(t_command *cmd, int control_fd, int fd[2])
// {
// 	// int	hdoc_control;

// 	// hdoc_control = 0;
// 	// if (cmd->redirs)
// 	// 	verif_heredoc(cmd->redirs, &hdoc_control);
// 	// if (g_exit_status == 130)
// 	// 	exit(130);
// 	if (control_fd != -1)
// 	{
// 		dup2(control_fd, STDIN_FILENO);
// 		close(control_fd);
// 	}
// 	if (cmd->next)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 	}
// 	if (cmd->redirs)
// 		definy_redir_fd(cmd);
// 	exec_child_proc(cmd);
// }

// static void	parent_proc(t_command *cmd, int *control_fd, int fd[2])
// {
// 	if (*control_fd != -1)
// 		close(*control_fd);
// 	if (cmd->next)
// 	{
// 		close(fd[1]);
// 		*control_fd = fd[0];
// 	}
// }

// void	exec_pipe(t_command *cmd)
// {
// 	int			fd[2];
// 	int			control_fd;
// 	pid_t		pid;
// 	t_command	*temp;

// 	control_fd = -1;
// 	temp = cmd;
// 	while (cmd)
// 	{
// 		if (cmd->next && pipe(fd) == -1)
// 			return ((void)printf("Error at pipe\n"));
// 		pid = fork();
// 		if (pid == -1)
// 			return ((void)printf("Error at fork\n"));
// 		if (pid == 0)
// 			child_proc(cmd, control_fd, fd);
// 		else
// 		{
// 			if (g_exit_status == 130)
// 				break ;
// 			parent_proc(cmd, &control_fd, fd);
// 			cmd = cmd->next;
// 		}
// 	}
// 	pipe_signal(temp, pid);
// }
