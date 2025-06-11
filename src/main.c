/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:10:45 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/11 12:30:57 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*get_shell(void)
{
	static t_shell	shell;
	
	return (&shell);
}

int	main(int argc, char **av, char **envp)
{
	t_shell	*shell;

	if (argc || av){
    ;
  }
  	shell = get_shell();
	init_t_shell(shell);
	// init_t_shell(get_shell());
	init_vars_from_envp(&shell->vars, envp);
	var_to_envp(shell);
	main_looping(shell);
	return (0);
}
