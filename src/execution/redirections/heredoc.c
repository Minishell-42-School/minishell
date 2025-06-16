/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/16 16:23:16 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	heredoc_child_proc(t_shell *shell, t_redirections *redir, \
			int heredoc_fd, int last_exit)
{
	heredoc_signals();
	loop_heredoc(shell, redir, heredoc_fd, last_exit);
	close(heredoc_fd);
	shell->hdoc_control = 1;
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

	file_name = tmpfile_name(&heredoc_fd);
	if (!file_name)
		return ;
	shell->hdoc_file = file_name;
	pid = fork();
	if (pid == -1)
	{
		fork_error(heredoc_fd, &file_name);
		return ;
	}
	if (pid == 0)
		heredoc_child_proc(shell, redir, heredoc_fd, last_exit);
	else
		heredoc_parent_proc(shell, pid, heredoc_fd);
	definy_redir(file_name, redir);
	shell->hdoc_control = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->term_backup);
	if (shell->last_status == 130)
		return ;
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
