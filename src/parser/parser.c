/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:08:20 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/12 16:56:38 by jcosta-b         ###   ########.fr       */
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
		return (NULL);
	last_cmd = first_cmd;
	while (p_state->current && p_state->current->type == PIPE)
	{
		advance_token(p_state);
		next_cmd = parse_command(v_error, p_state);
		if ((*v_error) || !next_cmd)
			return (NULL);
		last_cmd->next = next_cmd;
		last_cmd = next_cmd;
	}
	return (first_cmd);
}

static void	link_redir(t_command *cmd, t_redirections *redir)
{
	t_redirections	*last;

	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
}

static void	fill_cmd_args(t_parser_state *p_state, t_command *cmd, int *i)
{
	cmd->args[*i] = ft_strdup(p_state->current->value);
	if (*i == 0)
		cmd->command_name = ft_strdup(p_state->current->value);
	(*i)++;
	p_state->current = p_state->current->next;
}

t_command	*parse_command(int *v_error, t_parser_state *p_state)
{
	t_command		*cmd;
	t_redirections	*redir;
	int				i;

	cmd = init_command_struct(v_error);
	if (!cmd)
		return (NULL);
	cmd->args_count = count_args(p_state);
	cmd->args = malloc(sizeof(char *) * (cmd->args_count + 1));
	if (!cmd->args)
		return (error_malloc(&cmd, v_error));
	i = 0;
	while (p_state->current && p_state->current->type != PIPE)
	{
		if (p_state->current->type == WORD)
			fill_cmd_args(p_state, cmd, &i);
		else
		{
			redir = parse_redirection(v_error, p_state);
			link_redir(cmd, redir);
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
		return (error_redir(v_error, "Invalid redirection operator\n"));
	redir->filename = ft_strdup(p_state->current->value);
	redir->expand_hdoc = assign_hdoc_expansion(p_state->current);
	redir->next = NULL;
	advance_token(p_state);
	return (redir);
}
