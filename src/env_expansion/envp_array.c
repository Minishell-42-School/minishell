/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:07:47 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/26 18:09:36 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	build_envp(t_var *v, t_aux *aux, char **envp);

void	var_to_envp(t_var *vars)
{
	t_aux	aux;
	t_var	*v;
	char	**envp;	

	aux.count = 0;
	aux.i = 0;
	v = vars;
	while (v)
	{
		if (v->exported)
			aux.count++;
		v = v->next;
	}
	envp = malloc((aux.count + 1) * sizeof(char *));
	if (!envp)
		return (-1);
	v = vars;
	if (build_envp(v, &aux, envp) < 0)
	{
		free(envp);
		return (-1);
	}
	envp[aux.i] = NULL;
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
