/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:09:03 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/18 18:14:41 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//returns current token and advances state to the next
t_token	*advance_token(t_parser_state *p_state)
{
	t_token	*token;

	token = p_state->current;
	if (p_state->current != NULL)
		p_state->current = p_state->current->next;
	return (token);
}

t_command	*init_command_struct(int *v_error)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		ft_error(v_error, "Malloc cmd failed\n");
		return (NULL);
	}
	cmd->command_name = NULL;
	cmd->args = NULL;
	cmd->args_count = 0;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	count_args(t_parser_state *p_state)
{
	t_parser_state	temp;
	int				arg_count;

	temp = *p_state;
	arg_count = 0;
	while (temp.current && temp.current->type != PIPE)
	{
		if (temp.current->type == WORD)
		{
			arg_count++;
			temp.current = temp.current->next;
		}
		else
		{
			temp.current = temp.current->next;
			if (temp.current && temp.current->type == WORD)
				temp.current = temp.current->next;
		}
	}
	return (arg_count);
}

void	fill_cmd_args(int *v_error, t_parser_state *p_state,
	t_command *cmd, int *i)
{
	if (!p_state->current->value)
	{
		if (*i == 0)
		{
			ft_printf_stderr("'': command not found\n");
			(*v_error) = 127;
			return ;
		}
		cmd->args[*i] = ft_strdup("");
	}
	else
	{
		cmd->args[*i] = ft_strdup(p_state->current->value);
		if (*i == 0)
			cmd->command_name = ft_strdup(p_state->current->value);
	}
	(*i)++;
	p_state->current = p_state->current->next;
}

t_command	*verif_parse_cmd(int *v_error, t_parser_state *p_state)
{
	t_command	*cmd;

	cmd = init_command_struct(v_error);
	if (!cmd)
		return (NULL);
	cmd->args_count = count_args(p_state);
	cmd->args = malloc(sizeof(char *) * (cmd->args_count + 1));
	if (!cmd->args)
		return (error_malloc(&cmd, v_error));
	return (cmd);
}
