/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:08:20 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/18 17:03:56 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*parse_pipeline(int *v_error, t_parser_state *p_state)
{
	t_command	*first_cmd;
	t_command	*next_cmd;
	t_command	*last_cmd;

	if (check_syntax(p_state, v_error) == 1)
		return (NULL);
	first_cmd = parse_command(v_error, p_state);
	if ((*v_error))
		return (first_cmd);
	last_cmd = first_cmd;
	while (p_state->current && p_state->current->type == PIPE)
	{
		advance_token(p_state);
		next_cmd = parse_command(v_error, p_state);
		if (!next_cmd)
			return (NULL);
		last_cmd->next = next_cmd;
		last_cmd = next_cmd;
		if (*v_error)
			return (first_cmd);
	}
	return (first_cmd);
}

t_command	*parse_command(int *v_error, t_parser_state *p_state)
{
	t_command		*cmd;
	t_redirections	*redir;
	int				i;

	cmd = verif_parse_cmd(v_error, p_state);
	i = 0;
	while (p_state->current && p_state->current->type != PIPE)
	{
		if (p_state->current->type == WORD)
			fill_cmd_args(v_error, p_state, cmd, &i);
		else
		{
			redir = parse_redirection(v_error, p_state);
			link_redir(cmd, redir);
		}
		if ((*v_error) == 127)
		{
			free(cmd->args);
			free(cmd);
			return (NULL);
		}
	}
	cmd->args[i] = NULL;
	return (cmd);
}

//assigns the redirection type to t_redirections which is a
//component of t_command advances to the next token which must
//be a word and assign the word as redirection file
t_redirections	*parse_redirection(int *v_error, t_parser_state *p_state)
{
	t_redirections	*redir;

	if (!p_state->current)
		return (error_redir(v_error, \
				"Unexpected end of tokens while parsing redirection\n"));
	redir = malloc(sizeof(t_redirections));
	if (!redir)
		return (error_redir(v_error, "Malloc parser redirection failed\n"));
	redir = assign_redir_type(p_state, redir);
	if (!redir)
		return (error_redir(v_error, "Invalid redirection operator\n"));
	if (!p_state->current || p_state->current->type != WORD)
	{
		free(redir);
		return (error_redir(v_error, "Invalid redirection operator\n"));
	}
	redir->filename = ft_strdup(p_state->current->value);
	redir->expand_hdoc = assign_hdoc_expansion(p_state->current);
	redir->next = NULL;
	advance_token(p_state);
	return (redir);
}
