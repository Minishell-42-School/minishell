/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:51:51 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/19 11:06:16 by ekeller-@st      ###   ########.fr       */
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

void	free_redirections(t_redirections *redir)
{
	t_redirections	*temp;

	while (redir)
	{
		temp = redir->next;
		free(redir->filename);
		free(redir);
		redir = temp;
	}
}

void	free_command_list(t_command *head)
{
	t_command	*temp;
	int			i;

	while (head)
	{
		temp = head->next;
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
		head = temp;
	}
}

void	free_all(t_token **token_lst, t_command **cmd)
{
	if (*token_lst)
		free_token_lst(token_lst);
	if (*cmd)
	{
		free_command_list(*cmd);
		*cmd = NULL;
	}
}

void	free_vars(t_var *vars)
{
	while (vars)
	{
		if (vars->value)
			free(vars->value);
		if (vars->key)
			free(vars->key);
		vars = vars->next;
	}
}