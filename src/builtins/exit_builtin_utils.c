/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:19:49 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/18 16:34:13 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_numeric(const char *str)
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
	long	max;
	long	min;

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

long	ft_atol(const char *str, int *overflow)
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
