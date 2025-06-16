/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:51:51 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/12 18:03:20 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token_lst(t_token **token_lst)
{
	t_token	*tmp;

	if (!token_lst || !*token_lst)
		return ;
	while (*token_lst)
	{
		tmp = (*token_lst)->next;
		if ((*token_lst)->value)
			free((*token_lst)->value);
		if ((*token_lst)->expand_var)
			free((*token_lst)->expand_var);
		free(*token_lst);
		*token_lst = tmp;
	}
	*token_lst = NULL;
}

static void	free_redirections(t_shell *shell, t_redirections *redir)
{
	t_redirections	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (!shell->hdoc_control && \
			ft_strncmp(redir->filename, "/tmp/.hdoc_tmp_", 15) == 0)
			unlink(redir->filename);
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_command_list(t_shell *shell, t_command *head)
{
	t_command	*tmp;
	int			i;

	while (head)
	{
		tmp = head->next;
		if (head->command_name)
			free(head->command_name);
		if (head->args)
		{
			i = 0;
			while (head->args[i])
				free(head->args[i++]);
			free(head->args);
		}
		if (head->redirs)
			free_redirections(shell, head->redirs);
		free(head);
		head = tmp;
	}
}

void	free_loop(t_shell *shell)
{
	if (shell->token_list)
		free_token_lst(&shell->token_list);
	if (shell->cmd)
	{
		free_command_list(shell, shell->cmd);
		shell->cmd = NULL;
	}
}
