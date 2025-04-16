/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:16:47 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/22 13:13:44 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// This function outputs the int 'n' to the given file descriptor.

void	ft_putnbr_fd(int n, int fd)
{
	char	conv_to_str;

	conv_to_str = '0';
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n = -(n + 1);
			conv_to_str = '1';
		}
		else
			n = -n;
		ft_putchar_fd(45, fd);
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + conv_to_str, fd);
}
