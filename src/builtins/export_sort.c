/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 10:10:39 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/03 10:51:59 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_exported(t_var *vars)
{
	int	count;

	count = 0;
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
	int		i;
	int		j;
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
	int	i;

	i = 0;
	while (vars)
	{
		if (vars->exported)
			arr[i++] = vars;
		vars = vars->next;
	}
	arr[i] = NULL;
}

static void	print_var_line(t_var *var)
{
	printf("declare -x ");
	printf("%s", var->key);
	if (var->value)
	{
		printf("=\"");
		printf("%s", var->value);
		printf("\"");
	}
	printf("\n");
}

int	print_sorted_export(t_var *vars)
{
	t_var	**arr;
	int		count;
	int		i;

	count = count_exported(vars);
	arr = malloc(sizeof(t_var *) * count);
	if (!arr)
		return (-1);
	fill_exported_array(arr, vars);
	sort_var_array(arr, count);
	i = 0;
	while (i < count)
		print_var_line(arr[i++]);
	free(arr);
	return (0);
}
