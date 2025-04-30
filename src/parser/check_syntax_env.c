/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:07:16 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/04/30 17:37:49 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_syntax(t_parser_state *token)
{
	t_parser_state	temp;

	if (!token || !token->current)
		return (0);
	temp = *token;
	if (temp.current && temp.current->type == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}	
	while (temp.current && temp.current->type != PIPE)
		temp.current = temp.current->next;
	if (!temp.current)
		return (0);
	if (temp.current->next && temp.current->next->type == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}

t_command	*init_env_info(t_parser_state *p_state, t_command *cmd)
{
	t_token	*temp;
	int		total_env_vars;

	temp = p_state->current;
	total_env_vars = 0;
	while (temp && temp->type == WORD)
	{
		total_env_vars += temp->nbr_env_var;
		temp = temp->next;
	}
	cmd->nbr_env_var = total_env_vars;
	if (total_env_vars > 0)
	{
		cmd->expand_var = malloc(total_env_vars * sizeof(int));
		if (!cmd->expand_var)
			ft_error("malloc cmd->expand_var failed\n");
	}
	else
		cmd->expand_var = NULL;
	return (cmd);
}

t_command	*fill_cmd_args_envinfo(t_parser_state *p_state, t_command *cmd)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (p_state->current && p_state->current->type == WORD)
	{
		cmd->args[i] = ft_strdup(p_state->current->value);
		if (p_state->current->nbr_env_var > 0 && \
				p_state->current->expand_var != NULL)
		{
			j = 0;
			while (j < p_state->current->nbr_env_var)
				cmd->expand_var[k++] = p_state->current->expand_var[j++];
		}
		i++;
		advance_token(p_state);
	}
	cmd->args[i] = NULL;
	return (cmd);
}
