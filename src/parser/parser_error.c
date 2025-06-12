/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:08:20 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/12 16:56:12 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*error_malloc(t_command	**cmd, int *v_error)
{
	ft_error(v_error, "Malloc cmd args failed\n");
	free(cmd);
	return (NULL);
}

t_redirections	*error_redir(int *v_error, char *msg)
{
	ft_printf_stderr("%s", msg);
	(*v_error) = 1;
	return (NULL);
}

void	ft_error(int *v_error, char *msg)
{
	ft_printf_stderr("%s", msg);
	(*v_error) = 1;
}
