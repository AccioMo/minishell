/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:15:02 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/16 21:00:20 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_change_env_value(t_shell *env, char *name, char *value)
{
	int	i;

	i = 0;
	while (env->env[i])
	{
		if (ft_strncmp(env->env[i], name, ft_strlen(name)) == 0)
		{
			free(env->env[i]);
			env->env[i] = ft_strjoin(name, value);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	if (env->env[i] == NULL)
	{
		env->env = ft_realloc_env(env->env, i + 1, ft_strjoin(name, value));
		if (!env->env)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_cd(t_token *token, t_shell *env)
{
	if (token->args[1] == NULL && (chdir(ft_getenv("HOME", env->env)) == -1))
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR);
		return (EXIT_FAILURE);
	}
	else if (token->args[1] == NULL && ft_change_env_value(env, "OLDPWD",
		ft_getenv("PWD", env->env)) && ft_change_env_value(env, "PWD", ft_getenv("HOME", env->env)))
		return (EXIT_FAILURE);
	else if (chdir(token->args[1]) == -1)
	{
		ft_putstr_fd("cd: ", STDERR);
		ft_putstr_fd(token->args[1], STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		return (EXIT_FAILURE);
	}
	else if (ft_change_env_value(env, "OLDPWD", ft_getenv("PWD", env->env))
		&& ft_change_env_value(env, "PWD", token->args[1]))
		return (EXIT_FAILURE);
	ft_change_env_value(env, "_", token->args[1]);//later khas njib l path dial last command
	return (EXIT_SUCCESS);
}
