/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:01:41 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/05 17:24:47 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_and_free_pwd(t_var **vars, char *oldpwd, char *pwd)
{
	vars_set(vars, "OLDPWD", oldpwd, 1);
	vars_set(vars, "PWD", pwd, 1);
	free(oldpwd);
	free(pwd);
}

int	cd_builtin(t_command *cmd, t_var **vars)
{
	char	*oldpwd;
	char	*pwd;

	if (cmd->args[2])
		return (printf_stderr("bash: cd: too many arguments\n"));
	oldpwd = getcwd(NULL, 0);
	if (!cmd->args[1])
	{
		pwd = var_get(*vars, "HOME");
		if (!pwd || chdir(pwd) != 0)
		{
			free(oldpwd);
			return (1);
		}
	}
	else if (chdir(cmd->args[1]) != 0)
	{
		free(oldpwd);
		return (printf_stderr("bash: cd: %s: No such file or directory",
				cmd->args[1]));
	}
	pwd = getcwd(NULL, 0);
	update_and_free_pwd(vars, oldpwd, pwd);
	return (0);
}

int	exec_cd_builtin(t_shell *s, t_command *cmd)
{
	int	exit;

	exit = cd_builtin(cmd, &s->vars);
	var_to_envp(s);
	return (exit);
}
