/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:10:45 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/08 16:23:03 by jcosta-b         ###   ########.fr       */
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
  cmd_pipeline = NULL;
	while (1)
	{
		line = get_prompt();
		if (!line)
			break ;
		get_token(&token_list, line);

    t_token	*tmp;
    tmp = token_list;
    int x = 0;
    while (tmp)
    {
      if (tmp->nbr_env_var > 0)
      {
        int i = 0;
        while (i < tmp->nbr_env_var)
        {
          printf("..Token %d: \ntype - %d | n_env %d -> Exp %d\n%s%s%s\n\n", x, tmp->type, tmp->nbr_env_var, tmp->expand_var[i], GREEN, tmp->value, RESET);
          i++;
        }
      }
      else if (tmp->value[0] == '\0' || !tmp->value[0])
        printf("..Token %d: \ntype %d | String vazia %s%s%s\n\n", x, tmp->type, GREEN, tmp->value, RESET);
      else
          printf("..Token %d: \ntype - %d | n_env %d | %s%s%s\n\n", x, tmp->type, tmp->nbr_env_var, GREEN, tmp->value, RESET);
      x++;
      tmp = tmp->next;
    }


    if (token_list)
    {
      p_state.current = token_list;
      cmd_pipeline = parse_pipeline(&p_state);
      if (cmd_pipeline)
        exec_cmd(cmd_pipeline);
    }
    free_all(&token_list, &cmd_pipeline);
		free(line);
	}
	return (0);
}
