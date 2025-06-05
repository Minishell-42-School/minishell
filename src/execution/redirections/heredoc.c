/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/05 15:38:57 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	heredoc_child_proc(t_redirections *redir, int heredoc_fd)
{
	heredoc_signals();
	if (!loop_heredoc(redir, heredoc_fd))
		exit(EXIT_FAILURE);
	close(heredoc_fd);
	exit(EXIT_SUCCESS);
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

static void	handle_heredoc(t_shell *shell, t_redirections *redir)
{
	pid_t	pid;
	char	*file_name;
	int		heredoc_fd;

	file_name = tmpfile_name(&heredoc_fd);
	if (!file_name)
		return ;
	pid = fork();
	if (pid == -1)
	{
		fork_error(heredoc_fd, &file_name);
		return ;
	}
	if (pid == 0)
		heredoc_child_proc(redir, heredoc_fd);
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

void	verif_heredoc(t_shell *shell)
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
				handle_heredoc(shell, redir);
				if (shell->last_status == 130)
					return ;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
