/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:10:45 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/10 16:32:54 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **av, char **envp)
{
	t_shell	shell;

	if (argc || av)
		;
	init_t_shell(&shell);
	init_vars_from_envp(&shell.vars, envp);
	var_to_envp(&shell);
	main_looping(&shell);
	free_vars_and_envp(shell.vars, shell.new_envp);
	return (0);
}
