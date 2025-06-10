/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:19:49 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/10 15:41:19 by ekeller-@st      ###   ########.fr       */
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

static void	exit_without_arg(t_shell *s)
{
    cleanup_and_exit(s, s->last_status);
}

static void	exit_with_error_numeric(t_shell *s, char *arg)
{
    ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
    ft_putstr_fd(arg, STDERR_FILENO);
    ft_putendl_fd(": numeric argument required", STDERR_FILENO);
    cleanup_and_exit(s, 2);
}

int	exec_exit_builtin(t_shell *s, t_command *cmd)
{
    char    *arg;
    long    status;

    arg = cmd->args[1];
    printf("exit\n");
    if (!arg)
    {
        exit_without_arg(s);
    }
    if (!is_numeric(arg))
    {
        exit_with_error_numeric(s, arg);
    }
    if (cmd->args[2])
    {
        ft_putendl_fd("minishell: exit: too many arguments",
        STDERR_FILENO);
        return (1);
    }
    status = ft_atol(arg);
    cleanup_and_exit(s, (unsigned char)status);
	return (0);
}
