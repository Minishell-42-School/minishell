/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:11:53 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/14 18:12:13 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	handle_out(t_redirections *redir)
{
	int	fd;

	if (redir->type == R_OUT) // >
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else // >>
		fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("Error for open the file");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("Error - dup");
		close(fd);
		return ;
	}
	close(fd);
}

void	handle_in(t_redirections *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY); // <
	if (fd == -1)
	{
		perror("Error for open the file");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("Error - dup");
		close(fd);
		return ;
	}
	close(fd);
}

void	handle_creat(t_redirections *redir)
{
	int	fd;

	fd = open(redir->filename, O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Error for open the file");
		return ;
	}
	close(fd);
}

static void	loop_heredoc(t_redirections *redir, int fd)
{
	char	*line;

  while (1)
  {
    line = readline("Heredoc ~> ");
    if (!line)
    {
      printf("Warning: Use the delimiter by end-of-file, or press Ctrl + C to close\n");
      line = malloc(1 * sizeof(char));
      line[0] = '\0';
    }
    if (ft_strncmp(line, redir->filename, ft_strlen(redir->filename)) == 0)
    {
      free(line);
      break ;
    }
    write(fd, line, ft_strlen(line));
    if (line[0] != '\0')
      write(fd, "\n", 1);
    free(line);
  }
}

void	handle_heredoc(t_redirections *redir)
{
	int		heredoc_fd[2];

	if (pipe(heredoc_fd) == -1)
	{
		perror("pipe");
		return ;
	}
  loop_heredoc(redir, heredoc_fd[1]);
	close(heredoc_fd[1]);
  if (dup2(heredoc_fd[0], STDIN_FILENO) == -1)
  {
    perror("dup2");
    close(heredoc_fd[0]);
    return ;
  }
  close(heredoc_fd[0]);
}
