/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/11 12:37:50 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	heredoc_child_proc(t_shell *shell, t_redirections *redir, \
            int heredoc_fd, t_child_p_hdoc *child_hdoc)
{
	heredoc_signals();
	free(child_hdoc->file_name);
  	loop_heredoc(shell, redir, heredoc_fd, child_hdoc->last_exit);
  	close(heredoc_fd);
	
  	// Check if we received a signal
  	// if (g_signal == SIGINT)
  	// {
  	//   // Clean up and exit with appropriate status for SIGINT
  	//   free_all(shell, 130);
  	// }
  	
  	// Normal exit path
  	free_all(shell, 0);
}

static void	heredoc_parent_proc(t_shell *shell, pid_t pid, int heredoc_fd)
{
	int	status;

	ign_signals();
	waitpid(pid, &status, 0);
	config_signals();
	close(heredoc_fd);
	if (WIFSIGNALED(status))
		shell->last_status = 128 + WTERMSIG(status);
	else
		shell->last_status = WEXITSTATUS(status);
}

static void	handle_heredoc(t_shell *shell, t_redirections *redir, int last_exit)
{
	pid_t	pid;
	char	*file_name;
	int		heredoc_fd;
  t_child_p_hdoc child_hdoc;

  file_name = tmpfile_name(&heredoc_fd);
	if (!file_name)
    return ;
  // init_child_hdoc(&child_hdoc, &file_name, last_exit);
  child_hdoc.file_name = file_name;
  child_hdoc.last_exit = last_exit;
	pid = fork();
	if (pid == -1)
	{
		fork_error(heredoc_fd, &file_name);
		return ;
	}
	if (pid == 0)
    heredoc_child_proc(shell, redir, heredoc_fd, &child_hdoc);
	else
	{
		heredoc_parent_proc(shell, pid, heredoc_fd);
    if (shell->last_status == 0)
			definy_redir(file_name, redir);
		else
			clean_filename(&file_name);
		if (shell->last_status == 130)
			return ;
	}
}

void	verif_heredoc(t_shell *shell, int last_exit)
{
	t_redirections	*redir;
	t_command		*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == R_HEREDOC)
			{
				handle_heredoc(shell, redir, last_exit);
				if (shell->last_status == 130)
					return ;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
