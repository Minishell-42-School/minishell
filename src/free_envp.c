/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:43:45 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/10 14:39:10 by ekeller-@st      ###   ########.fr       */
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
	t_var	*temp;
	
	while (vars)
	{
	
		temp = vars->next;
		if (vars->value)
			free(vars->value);
		if (vars->key)
			free(vars->key);
		free(vars);
		vars = temp;
	}
	free_new_envp(new_envp);
}
