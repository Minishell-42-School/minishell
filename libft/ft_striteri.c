/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:22:09 by jcosta-b          #+#    #+#             */
/*   Updated: 2024/10/31 11:08:37 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Apply the function 'f' to each character of a string passed
// as an argument, passing its index as the first argument.
// Each character is passed by address to 'f' to be modified if necessary.

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
