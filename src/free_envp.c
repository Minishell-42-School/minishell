/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:43:45 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/21 14:12:03 by ekeller-@st      ###   ########.fr       */
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
	if (new_envp)
		free(new_envp);
}
