/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:43:45 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/11 12:47:22 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_new_envp(char **new_envp)
{
	int	i;

	i = 0;
	if (!new_envp)
		return ;
	while (new_envp[i])
		free(new_envp[i++]);
	free(new_envp);
	new_envp = NULL;
}

void	free_vars_and_envp(t_var *vars, char **new_envp)
{
	t_var	*tmp;

	while (vars)
	{
		tmp = vars->next;
		if (vars->value)
			free(vars->value);
		if (vars->key)
			free(vars->key);
		free(vars);
		vars = tmp;
	}
	if (new_envp)
		free_new_envp(new_envp);
}
