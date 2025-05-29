/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:18:27 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/29 17:48:19 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include "minishell.h"

static int	count_exported(t_var *vars)
{
	int	count = 0;
	while (vars)
	{
		if (vars->exported)
			count++;
		vars = vars->next;
	}
	return (count);
}

static void	sort_var_array(t_var **arr, int size)
{
	int		i, j;
	t_var	*tmp;
	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(arr[i]->key, arr[j]->key) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	fill_exported_array(t_var **arr, t_var *vars)
{
	int	i = 0;
	while (vars)
	{
		if (vars->exported)
			arr[i++] = vars;
		vars = vars->next;
	}
}

static void	print_var_line(t_var *var)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(var->key, STDOUT_FILENO);
	if (var->value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(var->value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	print_sorted_export(t_var *vars)
{
	t_var	**arr;
	int		count, i;

	count = count_exported(vars);
	arr = malloc(sizeof(t_var *) * count);
	if (!arr)
		return ;
	fill_exported_array(arr, vars);
	sort_var_array(arr, count);
	i = 0;
	while (i < count)
		print_var_line(arr[i++]);
	free(arr);
}
