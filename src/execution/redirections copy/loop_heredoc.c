/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/04 11:13:49 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int expand_line(t_shell *shell, t_hdoc_env_var *hdoc, char *line)
{
	int i = 0;

	while (line[i])
	{
		if (line[i] == '$' && line[i + 1])
		{
			str_until_now(hdoc, line, i);
			if (hdoc->value)
			{
				free(hdoc->value);
				hdoc->value = NULL;
			}
			expand_var(hdoc, line, &i, shell);
			if (hdoc->value)
        join_value(hdoc);
		}
		else
			i++;
	}
	return (i);
}

static void  init_hdoc(t_hdoc_env_var *hdoc, int l_exit)
{
  hdoc->result = NULL;
	hdoc->value = NULL;
	hdoc->start = 0;
  if (l_exit)
    hdoc->last_exit = l_exit;
  else
    hdoc->last_exit = 0;
}

static char *expand_env_var(t_shell *shell, char *line, int last_exit)
{
	t_hdoc_env_var hdoc;
	char *str;
	char *tmp;
	int i;

	init_hdoc(&hdoc, last_exit);
	i = expand_line(shell, &hdoc, line);
	if ((i - hdoc.start) > 0)
	{
		str = ft_substr(line, hdoc.start, i - hdoc.start);
		if (!hdoc.result)
			hdoc.result = str;
		else
		{
			tmp = hdoc.result;
			hdoc.result = ft_strjoin(hdoc.result, str);
			free(tmp);
			free(str);
		}
	}
	if (hdoc.value)
		free(hdoc.value);
	if (!hdoc.result)
		return (ft_strdup(line));
	return (hdoc.result);
}

static void  write_exp_line(t_shell *shell, int heredoc_fd, char *line, int last_exit)
{
  char  *expanded;

  expanded = expand_env_var(shell, line, last_exit);
  write(heredoc_fd, expanded, ft_strlen(expanded));
  write(heredoc_fd, "\n", 1);
  free(expanded);
}

int	loop_heredoc(t_shell *shell, t_redirections *redir, int heredoc_fd, \
    int last_exit)
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
    if (redir->expand_hdoc == EXPAND)
      write_exp_line(shell, heredoc_fd, line, last_exit);
    else
    {
      write(heredoc_fd, line, ft_strlen(line));
      write(heredoc_fd, "\n", 1);
    }
		free(line);
	}
	return (1);
}
