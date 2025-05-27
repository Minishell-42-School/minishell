/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:15:39 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/21 18:11:16 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	definy_redir_fd(t_command *cmd)
{
	t_redirections	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == R_DELIMITER)
		{
			redir = redir->next;
			continue ;
		}
		while (redir->next && ((redir->type == R_IN && \
			redir->next->type == R_IN) || \
			((redir->type == R_OUT || redir->type == R_APPEND) && \
			(redir->next->type == R_OUT || redir->next->type == R_APPEND))))
		{
			handle_creat(redir);
			redir = redir->next;
		}
		if (redir->type != R_DELIMITER)
		{
			if (redir->type == R_OUT || redir->type == R_APPEND)
				handle_out(redir);
			else// if (redir->type == R_IN)
				handle_in(redir);
		}
		redir = redir->next;
	}
}

void	verif_heredoc(t_redirections *redir, int *hdoc_control)
{
	while (redir)
	{
		if (redir->type == R_DELIMITER)
		{
			handle_heredoc(redir);
			*hdoc_control = 1;
			return ;
		}
		redir = redir->next;
	}
}

static void child_proc(t_command *cmd, int control_fd, int fd[2])
{
	char	*path;
	int		hdoc_control = 0;

	// signal(SIGINT, SIG_DFL);
	if (cmd->redirs)
		verif_heredoc(cmd->redirs, &hdoc_control);
  if (g_exit_status == 130)
    exit(130);
	if (!hdoc_control && control_fd != -1)
	{
		dup2(control_fd, STDIN_FILENO);
		close(control_fd);
	}
	if (cmd->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (cmd->redirs)
		definy_redir_fd(cmd);
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


static void	parent_proc(t_command *cmd, int *control_fd, int fd[2])
{
	if (*control_fd != -1)
		close(*control_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*control_fd = fd[0];
	}
}

void	exec_pipe(t_command *cmd)
{
	int		fd[2];
	int		control_fd;
	pid_t	pid;
  t_command *temp;
  t_redirections *r;

  g_exit_status = 0;
  printf("-> global - %d\n", g_exit_status);
	control_fd = -1;
  temp = cmd;
	while (cmd)
	{
		if (cmd->next && pipe(fd) == -1)
			return ((void)printf("Error at pipe\n"));
		pid = fork();
		if (pid == -1)
			return ((void)printf("Error at fork\n"));
		if (pid == 0)
			child_proc(cmd, control_fd, fd);
		else
		{
      // parent_proc(&control_fd, fd, cmd->next != NULL);
      if (g_exit_status == 130)
        break ;
			parent_proc(cmd, &control_fd, fd);
			cmd = cmd->next;
		}
	}
	// while (wait(NULL) > 0)
	// {
	// }
  int status;
  // while (wait(&status) > 0)
  // {
  //     if (WIFSIGNALED(status))
  //       g_exit_status = WEXITSTATUS(status);
  //     //     g_exit_status = 128 + WTERMSIG(status);
  //     // else
  // }
  ign_signals();
  while (waitpid(pid, &status, 0) > 0)
  {
    config_signals();
    if (WIFSIGNALED(status))
      g_exit_status = 128 + WTERMSIG(status);
    else
      g_exit_status = WEXITSTATUS(status);
    if (g_exit_status == 130)
    {
      while (temp)
      {
        if (temp->redirs)
        {
          r = temp->redirs;
          while (r)
          {
            if (r->type == R_OUT || r->type == R_APPEND)
              unlink(r->filename);
            r = r->next;
          }
        }
        temp = temp->next;
      }
      free_command_list(temp);
    }
  }
}
