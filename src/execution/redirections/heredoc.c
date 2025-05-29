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

void	close_hdoc_files(t_redirections *redirs)
{
	t_redirections	*redir;

	redir = redirs;
	while (redir)
	{
		// if (ft_strncmp(redir->filename, "/tmp/.hdoc_tmp_", 15))
		if (ft_strncmp(redir->filename, "./hdoc_tmp_", 15))
			unlink(redir->filename);
		redir = redir->next;
	}

}

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

static char	*loop_heredoc(t_redirections *redir)
{
	char	*file_name;
	char	*line;
	int		heredoc_fd;

	file_name = tmpfile_name(&heredoc_fd);
	printf("1. %s\n", file_name);
	// heredoc_fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (heredoc_fd == -1)
	{
		perror("Error at heredoc");
		return (NULL);//(0);
	}
	while (1)
	{
		line = readline("Heredoc ~> ");
		if (!line)
		{
			printf("Warning: here-document delimited by end-of-file\n");
			free(line);
			break ;
		}
		if (ft_strncmp(line, redir->filename, ft_strlen(redir->filename)) == 0)
		{
			free(line);
			break ;
		}
		write(heredoc_fd, line, ft_strlen(line));
		// if (line[0] != '\0')
			write(heredoc_fd, "\n", 1);
		free(line);
	}
	close(heredoc_fd);
	// free(redir->filename);
	// redir->filename = tmp_file;//ft_strdup(tmp_file);
	// printf("2. %s\n", tmp_file);
	// redir->type = R_IN;
	return (file_name);
}


static char	*hdoc_child_proc(t_redirections *redir)
{
	// close(hdo_fd[0]);
	heredoc_signals();
	return(loop_heredoc(redir));
	// close(hdo_fd[1]);
	// exit(EXIT_SUCCESS);
}

static void	hdoc_parent_proc(pid_t pid)
{
	int	status;

	// close(hdo_fd[1]);
	ign_signals();
	waitpid(pid, &status, 0);
	config_signals();
	if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	else
		g_exit_status = WEXITSTATUS(status);
	// if (dup2(hdo_fd[0], STDIN_FILENO) == -1)
	// 	perror("dup2");
	// close(hdo_fd[0]);
}

void	handle_heredoc(t_redirections *redir)
{
	// int		heredoc_fd[2];
	pid_t	pid;
	char	*file_name;

	// if (pipe(heredoc_fd) == -1)
	// {
	// 	perror("pipe");
	// 	return ;
	// }
	file_name = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		// close(heredoc_fd[0]);
		// close(heredoc_fd[1]);
		return ;
	}
	if (pid == 0)
		file_name = hdoc_child_proc(redir);
	else
	{
		hdoc_parent_proc(pid);
	}
	if (g_exit_status != 130)
	{
		free(redir->filename);
		redir->filename = file_name;
		redir->type = R_IN;
	}
	// PENSAR NO CASO DE CTRL C
}

int	verif_heredoc1(t_redirections *redir)
{
	int	if_heredoc;

	if_heredoc = 0;
	while (redir)
	{
		if (redir->type == R_DELIMITER)
		{
			handle_heredoc(redir);
			if_heredoc = 1;
		}
		redir = redir->next;
	}
	return (if_heredoc);
}
// ------------------------------------

// bool	preprocess_heredocs(t_command *cmd)
// {
// 	while (cmd)
// 	{
// 		t_redirections *redir = cmd->redirs;
// 		while (redir)
// 		{
// 			if (redir->type == R_DELIMITER)
// 			{
// 				if (!handle_heredoc_before_fork(redir))
// 					return false; // Erro ou Ctrl+C
// 			}
// 			redir = redir->next;
// 		}
// 		cmd = cmd->next;
// 	}
// 	return true;
// }


// bool	handle_heredoc_before_fork(t_redirections *redir)
// {
// 	char	*tmp_name = tmpfile_name(); // Crie um nome único, ex: "/tmp/.heredoc_XXXX"
// 	int		fd = open(tmp_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);

// 	if (fd == -1)
// 		return (perror("heredoc open"), false);

// 	// Grave o conteúdo do heredoc no arquivo tmp
// 	char *line;
// 	while (1)
// 	{
// 		line = readline("Heredoc ~> ");
// 		if (!line || ft_strcmp(line, redir->filename) == 0)
// 			break ;
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	free(line);
// 	close(fd);

// 	// Substitui o nome do heredoc pela referência ao tmpfile
// 	free(redir->filename);
// 	redir->filename = ft_strdup(tmp_name);
// 	redir->type = R_IN;

// 	return true;
// }

// void	exec_cmd(t_command *cmd)
// {
// 	g_exit_status = 0;
// 	if (!cmd)
// 		return ;
// 	if (!preprocess_heredocs(cmd)) // ⬅️ CHAMADA NOVA
// 		return ;
// 	if (cmd->next)
// 	{
// 		exec_pipe(cmd);
// 		return ;
// 	}
// 	exec_simple_cmd(cmd);
// }


