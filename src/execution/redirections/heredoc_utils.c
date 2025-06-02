/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/02 10:57:54 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*tmpfile_name(int *heredoc_fd)
{
	int		fd;
	int		i;
	char	*new_file;
	char	*str_nbr;

	i = 0;
	while (i < 10000)
	{
		str_nbr = ft_itoa(i);
		new_file = ft_strjoin("/tmp/.hdoc_tmp_", str_nbr);
		free(str_nbr);
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

int	loop_heredoc(t_redirections *redir, int heredoc_fd)
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

void	definy_redir(char *file_name, t_redirections *redir)
{
	free(redir->filename);
	redir->filename = file_name;
	redir->type = R_IN;
}

void	clean_filename(char **file_name)
{
	unlink(*file_name);
	free(*file_name);
}

void	fork_error(int heredoc_fd, char **file_name)
{
	perror("fork");
	close(heredoc_fd);
	clean_filename(file_name);
}
