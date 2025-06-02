/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:07:47 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/27 14:02:06 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	build_envp(t_var *v, t_aux *aux, char **envp);

int	var_to_envp(t_shell *s)
{
	t_aux	aux;
	t_var	*v;

	aux.count = 0;
	aux.i = 0;
	if (s->new_envp)
		free_new_envp(s->new_envp);
	v = s->vars;
	while (v)
	{
		if (v->exported)
			aux.count++;
		v = v->next;
	}
	s->new_envp = malloc((aux.count + 1) * sizeof(char *));
	if (!s->new_envp)
		return (-1);
	v = s->vars;
	if (build_envp(v, &aux, s->new_envp) < 0)
	{
		free(s->new_envp);
		return (-1);
	}
	s->new_envp[aux.i] = NULL;
	return (0);
}

static int	build_envp(t_var *v, t_aux *aux, char **envp)
{
	char	*s;

	while (v)
	{
		if (v->exported)
		{
			aux->len = ft_strlen(v->key) + 1 + ft_strlen(v->value) + 1;
			s = malloc(aux->len);
			if (!s)
				return (-1);
			ft_strcpy(s, v->key);
			s[ft_strlen(v->key)] = '=';
			ft_strcpy(s + ft_strlen(v->key) + 1, v->value);
			envp[aux->i++] = s;
		}
		v = v->next;
	}
	return (0);
}
