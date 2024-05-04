/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:15:02 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/18 18:55:14 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_change_env_value(t_env *env, char *name, char *value)
{
	int	i;

	i = 0;
	while (env->env[i])
	{
		if (ft_strncmp(env->env[i], name, ft_strlen(name)) == 0)
		{
			free(env->env[i]);
			env->env[i] = ft_strjoin(name, value);
			return (SUCCESS);
		}
		i++;
	}
	if (env->env[i] == NULL)
	{
		env->env = ft_realloc_env(env->env, i + 1, ft_strjoin(name, value));
		if (!env->env)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_cd(t_cmds *cmd, t_env *env)
{
	if (cmd->cmd[1] == NULL)
	{
		if (chdir(ft_getenv("HOME", env->env)) == -1)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR);
			return (ERROR);
		}
		ft_change_env_value(env, "OLDPWD", ft_getenv("PWD", env->env));
		ft_change_env_value(env, "PWD", ft_getenv("HOME", env->env));
	}
	else
	{
		if (chdir(cmd->cmd[1]) == -1)
		{
			ft_putstr_fd("cd: ", STDERR);
			ft_putstr_fd(cmd->cmd[1], STDERR);
			ft_putstr_fd(": No such file or directory\n", STDERR);
			return (ERROR);
		}
		ft_change_env_value(env, "OLDPWD", ft_getenv("PWD", env->env));
		ft_change_env_value(env, "PWD", cmd->cmd[1]);
	}
	return (SUCCESS);
}
