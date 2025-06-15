/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:19:49 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/15 15:11:14 by ekeller-@st      ###   ########.fr       */
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

static int	would_overflow(long result, char digit, int sign)
{
	long max;
	long min;

	max = LONG_MAX;
	min = LONG_MIN;
	if (sign > 0)
	{
		if (result > max / 10)
			return (1);
		if (result == max / 10 && (digit - '0') > max % 10)
			return (1);
	}
	else
	{
		if (result > (-(min / 10)))
			return (1);
		if (result == (-(min / 10)) && (digit - '0') > (-(min % 10)))
			return (1);
	}
	return (0);
}

static long	ft_atol(const char *str, int *overflow)
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
		if (would_overflow(result, str[i], sign))
		{
			*overflow = 1;
			return (0);
		}
		result = result * 10 + (str[i++] - '0');
	}
	return (sign * result);
}

int	exec_exit_builtin(t_shell *s, t_command *cmd)
{
	char		*arg;
	long		status;
	int			overflow;

	overflow = 0;
	arg = cmd->args[1];
	printf("exit\n");
	if (!arg)
	{
		status = s->last_status;
		free_all(s, status);
	}
	status = ft_atol(arg, &overflow);
	if (!is_numeric(arg) || overflow)
	{
		ft_printf_stderr("minishell: exit: %s: numeric argument required", arg);
		free_all(s, 2);
	}
	if (cmd->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	free_all(s, (unsigned char)status);
	return (0);
}
