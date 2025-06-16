/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:19:49 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/12 15:58:28 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (i > 0);
}

static long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

int	exec_exit_builtin(t_shell *s, t_command *cmd, int std_in, int std_out)
{
	char		*arg;
	long		status;

	arg = cmd->args[1];
	printf("exit\n");
	if (!arg)
	{
		status = s->last_status;
    dup2(std_in, STDIN_FILENO);
		dup2(std_out, STDOUT_FILENO);
		close(std_in);
		close(std_out);
		free_all(s, status);
	}
	if (!is_numeric(arg))
	{
    ft_printf_stderr("minishell: exit %s: numeric argument required\n", arg);
    dup2(std_in, STDIN_FILENO);
		dup2(std_out, STDOUT_FILENO);
		close(std_in);
		close(std_out);

		// ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		// ft_putstr_fd(arg, STDERR_FILENO);
		// ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		free_all(s, 2);
	}
	if (cmd->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
    return (1);
	}
	status = ft_atol(arg);
  dup2(std_in, STDIN_FILENO);
  dup2(std_out, STDOUT_FILENO);
  close(std_in);
  close(std_out);
	free_all(s, (unsigned char)status);
	return (0);
}
