/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:01:26 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/30 15:15:47 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// This function outputs the caracter ’c’ to the given file descriptor.

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
