/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:55:17 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/08 16:33:55 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void  exec_child_proc(t_command *cmd)
{
  char  *path;

  // g_exit_status = 0;
  if (cmd->redirs)
    definy_fd(cmd);
  if (g_exit_status == 130)
    exit(130);
  path = get_path(cmd);
  if (!path)
    exit(EXIT_FAILURE);
  if (execve(path, cmd->args, NULL) == -1)
  {
    perror("execve");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

static void  exec_parent_proc(pid_t pid)
{
  int status;
  ign_signals();
  waitpid(pid, &status, 0);
  config_signals();
  if (WIFSIGNALED(status))
    g_exit_status = 128 + WTERMSIG(status);
  else
    g_exit_status = WEXITSTATUS(status);
}

void exec_simple_cmd(t_command *cmd)
{
    pid_t pid = fork();

    g_exit_status = 0;
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (pid == 0)
      exec_child_proc(cmd);
    else
      exec_parent_proc(pid);
}
