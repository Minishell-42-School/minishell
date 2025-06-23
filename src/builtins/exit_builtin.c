/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:19:49 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/23 13:25:54 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	many_arg(void)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	return (1);
}

void	clean_exit(t_shell *s, int status, int std_in, int std_out)
{
	dup2_and_close(std_in, std_out);
	free_all(s, status);
}

int	exec_exit_builtin(t_shell *s, t_command *cmd, int std_in, int std_out)
{
	char	*arg;
	long	status;
	int		overflow;

	overflow = 0;
	arg = cmd->args[1];
	printf("exit\n");
	if (!arg)
	{
		status = s->last_status;
		clean_exit(s, status, std_in, std_out);
	}
	status = ft_atol(arg, &overflow);
	if (!is_numeric(arg) || overflow)
	{
		ft_printf_stderr("minishell: exit: %s: numeric argument required\n", \
			arg);
		clean_exit(s, 2, std_in, std_out);
	}
	if (cmd->args[2])
		return (many_arg());
	clean_exit(s, (unsigned char)status, std_in, std_out);
	return (0);
}
