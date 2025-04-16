/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:14:42 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/30 15:14:13 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocate (with malloc) and return a string
// that represent an int received as an arg

static int	ft_strlen_itoa(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		if (n == -2147483648)
			n = -(n + 1);
		else
			n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	ft_negnumber(int n)
{
	if (n == -2147483648)
	{
		n = -(n + 1);
		n /= 10;
	}
	else
		n = -n;
	return (n);
}

static void	ft_str_itoa(int n, char *str, int len)
{
	while (len >= 0)
	{
		if (str[len] != '-')
			str[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_strlen_itoa(n);
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	len--;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			str[len] = '8';
			len--;
		}
		n = ft_negnumber(n);
		str[0] = '-';
	}
	ft_str_itoa(n, str, len);
	return (str);
}
