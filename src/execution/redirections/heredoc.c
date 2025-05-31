/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/29 18:22:40 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*tmpfile_name(int *heredoc_fd)
{
	int		fd;
	int		i;
	char	*new_file;

	i = 0;
	while (i < 10000)
	{
		// new_file = ft_strjoin("/tmp/.hdoc_tmp_", ft_itoa(i));
		new_file = ft_strjoin("./hdoc_tmp_", ft_itoa(i));
		fd = open(new_file, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd != -1)
		{
			*heredoc_fd = fd;
			return (new_file);
		}
		else
			free(new_file);
		i++;
	}
	perror("heredoc temp file");
	return (NULL);
}

static int loop_heredoc(t_redirections *redir, int heredoc_fd)
{
	char	*line;

	while (1)
	{
		line = readline("Heredoc ~> ");
		if (!line)
		{
			printf("Warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (ft_strncmp(line, redir->filename, ft_strlen(redir->filename)) == 0)
		{
			free(line);
			break ;
		}
		write(heredoc_fd, line, ft_strlen(line));
    write(heredoc_fd, "\n", 1);
		free(line);
	}
  return (1);
}

void	handle_heredoc(t_redirections *redir)
{
	pid_t	pid;
	char	*file_name;
	int		heredoc_fd;
	int		status;

	file_name = tmpfile_name(&heredoc_fd);
	if (!file_name)
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(heredoc_fd);
		unlink(file_name);
		free(file_name);
		return ;
	}
	if (pid == 0)
	{
		heredoc_signals();
		if (!loop_heredoc(redir, heredoc_fd))
			exit(EXIT_FAILURE);
		close(heredoc_fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		ign_signals();
		waitpid(pid, &status, 0);
		config_signals();
		close(heredoc_fd);

    if (WIFSIGNALED(status))
		  g_exit_status = 128 + WTERMSIG(status);
		else //if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
    // if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    // 		{

        // }
		if (g_exit_status == 0)
		{
			free(redir->filename);
			redir->filename = file_name;
			redir->type = R_IN;
		}
    else if (g_exit_status == 130)
    {
      unlink(file_name);
			free(file_name);
			return ;
    }
		else
		{
			unlink(file_name);
			free(file_name);
		}
	}
}

void	verif_heredoc1(t_command *command)
{
  t_redirections *redir;
  t_command      *cmd;

  cmd = command;
  while (cmd)
  {
    redir = cmd->redirs;
    while (redir)
    {
      if (redir->type == R_DELIMITER)
      {
        handle_heredoc(redir);
        if (g_exit_status == 130)
          return ;
      }
      redir = redir->next;
    }
    cmd = cmd->next;
  }
}
