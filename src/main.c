/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:10:45 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/08 14:04:06 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char			*line;
	t_token			*token_list;
	t_command		*cmd_pipeline;
	t_parser_state	p_state;

	token_list = NULL;
	while (1)
	{
		line = get_prompt();
		if (!line)
			break ;
		printf("Recebido: %s\n", line);
		get_token(&token_list, line);
		p_state.current = token_list;
		cmd_pipeline = parse_pipeline(&p_state);
		if (!cmd_pipeline)
		{
			clean_all(&token_list);
			free(line);
			continue ;
		}
		exec_external_cmd(cmd_pipeline);
		
		clean_all(&token_list);
		free(line);
		free_command_list(cmd_pipeline);
	}
	return (0);
}
