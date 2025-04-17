/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:10:45 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/04/17 17:49:32 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;
	t_token	*token_list;

	token_list = NULL;
	while (1)
	{
		line = get_prompt();
		if (!line)
			break ;
		// printf("Recebido: %s\n", line);
		get_token(&token_list, line);

		t_token	*tmp;
		tmp = token_list;
		while (tmp)
		{
			printf("....Token: type %d | %s%s%s\n", tmp->type, GREEN, tmp->value, RESET);
			tmp = tmp->next;
		}
		clean_all(&token_list);
		free(line);
	}
	return (0);
}
