/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:08:20 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/05 18:16:40 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*parse_pipeline(t_parser_state *p_state)
{
	t_command	*first_cmd;
	t_command	*next_cmd;
	t_command	*last_cmd;

	if (check_syntax(p_state) == 1)
		return (NULL);
	first_cmd = parse_command(p_state);
	last_cmd = first_cmd;
	while (p_state->current && p_state->current->type == PIPE)
	{
		advance_token(p_state);
		next_cmd = parse_command(p_state);
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
	char	*val;
	char	*dup;

	val = p_state->current->value;
	if (!val)
		dup = ft_strdup("");
	else
		dup = ft_strdup(val);
	cmd->args[*i] = dup;
	if (*i == 0)
	{
		if (!val)
			cmd->command_name = ft_strdup("");
		else
			cmd->command_name = ft_strdup(val);
	}
	(*i)++;
	p_state->current = p_state->current->next;
}

/*
	… rest of parser.c unchanged …
*/


t_command	*parse_command(t_parser_state *p_state)
{
	t_command		*cmd;
	t_redirections	*redir;
	int				i;

	cmd = init_command_struct();
	cmd->args_count = count_args(p_state);
	cmd->args = malloc(sizeof(char *) * (cmd->args_count + 1));
	if (!cmd->args)
		ft_error("Malloc cmd args failed\n");
	i = 0;
	while (p_state->current && p_state->current->type != PIPE)
	{
		if (p_state->current->type == WORD)
			fill_cmd_args(p_state, cmd, &i);
		else
		{
			redir = parse_redirection(p_state);
			link_redir(cmd, redir);
		}
	}
	cmd->args[i] = NULL;
	// cmd->pipe_pid = 0;
	return (cmd);
}

//assigns the redirection type to t_redirections which is a
//component of t_command advances to the next token which must
//be a word and assign the word as redirection file
t_redirections	*parse_redirection(t_parser_state *p_state)
{
	t_redirections	*redir;

	if (!p_state->current)
		ft_error("Unexpected end of tokens while parsing redirection\n");
	redir = malloc(sizeof(t_redirections));
	if (!redir)
		ft_error("Malloc parser redirection failed\n");
	redir = assign_redir_type(p_state, redir);
	if (p_state->current->type != WORD || !p_state->current)
		ft_error("Expected filename after redirection operator\n");
	redir->filename = ft_strdup(p_state->current->value);
	redir->next = NULL;
	advance_token(p_state);
	return (redir);
}
