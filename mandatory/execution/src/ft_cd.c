/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:15:02 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/23 13:34:42 by zouddach         ###   ########.fr       */
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
		env->env = ft_realloc_env(env->env,
				i + 1, ft_strjoin_free(name, value, 0));
		if (!env->env)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_first_condition(t_shell *shell)
{
	if (chdir(ft_getenv("HOME", shell->env)) == -1)
	{
		if (ft_getenv("HOME", shell->env) == NULL)
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR);
		else
		{
			ft_putstr_fd("minishell: cd: \n", STDERR);
			ft_putstr_fd(ft_getenv("HOME", shell->env), STDERR);
			ft_putstr_fd(": No such file or directory\n", STDERR);
		}
		return (EXIT_FAILURE);
	}
	if (ft_change_env_value(shell, "OLDPWD=", ft_getenv("PWD", shell->env)))
		return (EXIT_FAILURE);
	if (ft_change_env_value(shell, "PWD=", ft_getenv("HOME", shell->env)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_second_condition(t_shell *shell, char *pwd)
{
	if (chdir(ft_getenv("OLDPWD", shell->env)) == -1)
	{
		ft_putstr_fd("minishell : cd: ", STDERR);
		ft_putstr_fd(ft_getenv("OLDPWD", shell->env), STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		return (EXIT_FAILURE);
	}
	if (ft_change_env_value(shell, "OLDPWD=", ft_getenv("PWD", shell->env)))
		return (EXIT_FAILURE);
	if (ft_change_env_value(shell, "PWD=", getcwd(pwd, 255)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_token *token, t_shell *shell)
{
	char	pwd[255];

	if (token->args[1] == NULL && !ft_first_condition(shell))
		return (EXIT_SUCCESS);
	else if (token->args[1] == NULL)
		return (EXIT_FAILURE);
	else if (!ft_strncmp(token->args[1], "-\0", 2))
		return (ft_second_condition(shell, pwd));
	else
	{
		if (chdir(token->args[1]) == -1)
		{
			ft_putstr_fd("minishell : cd: ", STDERR);
			ft_putstr_fd(token->args[1], STDERR);
			ft_putstr_fd(": No such file or directory\n", STDERR);
			return (EXIT_FAILURE);
		}
		if (ft_change_env_value(shell, "OLDPWD=", ft_getenv("PWD", shell->env)))
			return (EXIT_FAILURE);
		if (ft_change_env_value(shell, "PWD=", getcwd(pwd, 255)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
