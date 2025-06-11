/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:51:51 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/03 11:21:13 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token_lst(t_token **token_lst)
{
	t_token	*tmp;

  printf("2. LIMPANDO TOKEN\n");
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

static void	free_redirections(t_redirections *redir)
{
	t_redirections	*tmp;

  printf("4. LIMPANDO REDIR\n");
	while (redir)
	{
		tmp = redir->next;
		if (ft_strncmp(redir->filename, "/tmp/.hdoc_tmp_", 15) == 0)
			unlink(redir->filename);
		free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_command_list(t_command *head)
{
	t_command	*tmp;
	int			i;

  printf("3. LIMPANDO CMD\n");
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
			free_redirections(head->redirs);
		free(head);
		head = tmp;
	}
}

void	free_loop(t_token **token_lst, t_command **cmd)
{
  printf("1. LIMPANDO\n");
	if (*token_lst)
		free_token_lst(token_lst);
	if (*cmd)
	{
		free_command_list(*cmd);
		*cmd = NULL;
	}
}
