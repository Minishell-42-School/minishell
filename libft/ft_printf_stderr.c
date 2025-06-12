/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stderr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:12:02 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/06/12 13:39:56 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	printf_putchar_err(char c)
{
	write(2, &c, 1);
	return (1);
}

size_t	printf_putstr_err(char *s)
{
	int	i;

	if (s == NULL)
		return (printf_putstr_err("(null)"));
	i = 0;
	while (s[i])
		i += printf_putchar_err(s[i]);
	return (i);
}

static size_t	printf_specifiers(va_list args, char c)
{
	size_t	printed;

	printed = 0;
	if (c == 'c')
		printed += printf_putchar_err(va_arg(args, int));
	else if (c == 's')
		printed += printf_putstr_err(va_arg(args, char *));
	else if (c == '%')
		printed += printf_putchar_err('%');
	return (printed);
}

int	ft_printf_stderr(const char *fmt_str, ...)
{
	va_list	args;
	int		i;
	size_t	printed;

	if (!fmt_str)
		return (-1);
	va_start(args, fmt_str);
	i = 0;
	printed = 0;
	while (fmt_str[i] != '\0')
	{
		if (fmt_str[i] == '%' && fmt_str[i + 1] != '\0')
		{
			i++;
			printed += printf_specifiers(args, fmt_str[i]);
			i++;
		}
		else
		{
			printed += printf_putchar_err(fmt_str[i]);
			i++;
		}
	}
	va_end(args);
	return (printed);
}