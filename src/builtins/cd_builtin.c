/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:01:41 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/23 16:49:38 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



int	cd_builtin(t_command *cmd, t_var **vars)
{
	int	i;

	i = 1;
	if (cmd->args[2])
	{
		pritnf ("cd: string not in pwd: %s\n", cmd->args[1]);
		return (-1);
	}	
	
}