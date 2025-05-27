/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:01:41 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/05/27 15:31:29 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	return_error(char *std_message, char *input)
{
	write(2, std_message, ft_strlen(std_message));
	write(2, input, ft_strlen(input));
	write(2, "\n", 1);
	return (-1);
}

static void	update_and_free_pwd(t_var **vars, char *oldpwd, char *pwd)
{
	vars_set(vars, "OLDPWD", oldpwd, 1);
	vars_set(vars, "PWD", pwd, 1);
	free(oldpwd);
	free(pwd);
}

int	cd_builtin(t_command *cmd, t_var **vars)
{
	char	*OLDPWD;
	char	*PWD;

	if (cmd->args[2])
		return (return_error("cd: string not in pwd: ", cmd->args[1]));
	OLDPWD = getcwd(NULL, 0);
	if (!cmd->args[1])
	{
		PWD = var_get(*vars, "HOME");
		if (!PWD || chdir(PWD) != 0)
		{
			free(OLDPWD);
			return (-1);
		}
	}
	else if (chdir(cmd->args[1]) != 0)
	{
		free(OLDPWD);
		return (return_error("cd: no such file or directory: ", cmd->args[1]));
	}
	PWD = getcwd(NULL, 0);
	update_and_free_pwd(vars, OLDPWD, PWD);
	return (0);
}

int	exec_cd_builtin(t_shell *s)
{
	cd_builtin(s->cmd, &s->vars);
	var_to_envp(s);
	return (0);
}