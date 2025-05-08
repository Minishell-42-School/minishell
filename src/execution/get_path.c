/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcosta-b <jcosta-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:55:17 by jcosta-b          #+#    #+#             */
/*   Updated: 2025/05/08 14:07:27 by jcosta-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_dir(char ***dir)
{
	int	i;

	i = 0;
	if (!dir || !*dir)
		return ;
	while ((*dir)[i])
	{
		free((*dir)[i]);
		i++;
	}
	free(*dir);
	*dir = NULL;
}

static char	*get_env_path(t_command *cmd, char ***dir)
{
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	while ((*dir)[i])
	{
		temp = ft_strjoin((*dir)[i], "/");
		if (!temp)
			break ;
		path = ft_strjoin(temp, cmd->command_name);
		free(temp);
		if (!path)
			break ;
		if (access(path, X_OK) == 0)
		{
			free_dir(dir);
			return (path);
		}
		free(path);
		i++;
	}
	free_dir(dir);
	return (NULL);
}

char	*get_path(t_command *cmd)
{
	char	*env_path;
	char	*path;
	char	**dir;

	dir = NULL;
	if (ft_strchr(cmd->command_name, '/'))
		path = cmd->command_name;
	else
	{
		env_path = getenv("PATH");
		if (!env_path)
			return (NULL);
		dir = ft_split(env_path, ':');
		if (!dir)
			return (NULL);
		path = get_env_path(cmd, &dir);
	}
	if (access(path, X_OK) != 0)
		perror("Command not found or not executable");
	return (path);
}
