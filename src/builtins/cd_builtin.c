/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeller-@student.42sp.org.br <ekeller-@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:01:41 by ekeller-@st       #+#    #+#             */
/*   Updated: 2025/06/18 17:12:40 by ekeller-@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_and_free_pwd(t_var **vars, char *oldpwd, char *pwd)
{
	if (oldpwd)
		vars_set(vars, "OLDPWD", oldpwd, 1);
	if (pwd)
		vars_set(vars, "PWD", pwd, 1);
	free(oldpwd);
	free(pwd);
}

static char	*check_pwd(char *pwd, t_var *vars)
{
	char	*home;
	
	if (!pwd)
	{
		home = var_get(vars, "HOME");
		if (home)
			pwd = ft_strdup(home);
	}	
	return (pwd);
}

int	cd_builtin(t_command *cmd, t_var **vars)
{
	char	*oldpwd;
	char	*pwd;

	if (cmd->args_count > 2)
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
		return (printf_stderr("cd: %s: No such file or directory\n",
				cmd->args[1]));
	}
	pwd = getcwd(NULL, 0);
	pwd = check_pwd(pwd, *vars);
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
