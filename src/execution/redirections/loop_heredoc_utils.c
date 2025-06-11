/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_heredoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:10:40 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/04 11:13:49 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	str_until_now(t_hdoc_env_var *hdoc, char *line, int i)
{
	char	*str;
	char	*tmp;

	str = ft_substr(line, hdoc->start, i - hdoc->start);
	if (!str)
		return ;
	if (!hdoc->result)
		hdoc->result = str;
	else
	{
		tmp = hdoc->result;
		hdoc->result = ft_strjoin(hdoc->result, str);
		free(tmp);
		free(str);
	}
}

static char	*get_key(char *line, int pos)
{
	char	*key;
	int		j;
	int		len;

	key = NULL;
	j = 0;
	len = pos;
	while (ft_isalnum(line[len]) || line[len] == '_')
		len++;
	len -= pos;
	key = malloc((len + 1) * sizeof(char));
	len = pos;
	while (ft_isalnum(line[len]) || line[len] == '_')
	{
		key[j] = line[len];
		j++;
		len++;
	}
	key[j] = '\0';
	return (key);
}

static void	find_value(t_hdoc_env_var *hdoc, char *line, int *i, t_shell *shell)
{
	char	*key;
	char	*tmp_value;
	int		key_len;

	key_len = 0;
	key = get_key(line, (*i) + 1);
	key_len = ft_strlen(key);
	tmp_value = var_get(shell->vars, key);
	if (tmp_value)
		hdoc->value = ft_strdup(tmp_value);
	else
		hdoc->value = ft_strdup("");
	free(key);
	(*i) += (key_len + 1);
}

void	expand_var(t_hdoc_env_var *hdoc, char *line, int *i, t_shell *shell)
{
	if (line[(*i) + 1] == '?')
	{
		hdoc->value = ft_itoa(hdoc->last_exit);
		(*i) += 2;
	}
	else if (ft_isalpha(line[(*i) + 1]) || line[(*i) + 1] == '_')
		find_value(hdoc, line, i, shell);
	else
	{
		hdoc->value = ft_strdup("$");
		(*i)++;
	}
	hdoc->start = (*i);
}

void	join_value(t_hdoc_env_var *hdoc)
{
	char	*tmp;

	tmp = hdoc->result;
	if (tmp)
	{
		hdoc->result = ft_strjoin(tmp, hdoc->value);
		free(tmp);
	}
	else
		hdoc->result = ft_strjoin("", hdoc->value);
}
