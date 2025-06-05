/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_stderr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:14:08 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/04 19:05:18 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>
#include <stdarg.h>
#include <string.h>

static void	write_str_stderr(char *str)
{
	char	*s;
	ssize_t	w;
	size_t	len;

	if (!str)
	{
		s = "(null)";
	}
	else
	{
		s = str;
	}
	len = strlen(s);
	w = write(2, s, len);
	(void)w;
}

int	printf_stderr(const char *format, ...)
{
	va_list	ap;
	char	*p;
	char	*s;

	va_start(ap, format);
	p = (char *)format;
	while ((s = strstr(p, "%s")))
	{
		write(2, p, s - p);
		write_str_stderr(va_arg(ap, char *));
		p = s + 2;
	}
	write(2, p, strlen(p));
	va_end(ap);
	return (1);
}
