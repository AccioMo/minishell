/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:15:02 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/20 17:17:47 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"

static int	ft_first_condition(t_shell *shell)
{
	if (ft_getenv("HOME", shell->env) == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR);
		return (EXIT_FAILURE);
	}
	if (chdir(ft_getenv("HOME", shell->env)) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR);
		ft_putstr_fd(ft_getenv("HOME", shell->env), STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		return (EXIT_FAILURE);
	}
	if (ft_set_env(shell, "OLDPWD", ft_getenv("PWD", shell->env)))
		return (EXIT_FAILURE);
	if (ft_set_env(shell, "PWD", ft_getenv("HOME", shell->env)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_second_condition(t_shell *shell, char *pwd)
{
	if (chdir(ft_getenv("OLDPWD", shell->env)) != 0)
	{
		ft_putstr_fd("minishell : cd: ", STDERR);
		ft_putstr_fd(ft_getenv("OLDPWD", shell->env), STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		return (EXIT_FAILURE);
	}
	if (ft_set_env(shell, "OLDPWD", ft_getenv("PWD", shell->env)))
		return (EXIT_FAILURE);
	if (ft_set_env(shell, "PWD", getcwd(pwd, 255)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_cd_error(char *path, t_shell *shell)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(path);
	if (shell == NULL)
		return (EXIT_FAILURE);
	ft_putstr_fd("error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory\n", 2);
	ft_set_env(shell, "PWD", path);
	return (EXIT_FAILURE);
}

int	ft_cd(t_token *token, t_shell *shell)
{
	char	pwd[PATH_MAX];
	char	*path;

	token->args[1] = ft_path(token->args[1], shell);
	path = token->args[1];
	if (path == NULL)
		return (EXIT_FAILURE);
	if (token->args[1] == NULL && !ft_first_condition(shell))
		return (EXIT_SUCCESS);
	else if (token->args[1] == NULL)
		return (EXIT_FAILURE);
	else if (!ft_strncmp(token->args[1], "-\0", 2))
		return (ft_second_condition(shell, pwd));
	else
	{
		if (chdir(path))
			return (ft_cd_error(path, NULL));
		if (getcwd(pwd, PATH_MAX) == NULL)
			return (ft_cd_error(path, shell));
		if (ft_set_env(shell, "OLDPWD", ft_getenv("PWD", shell->env)) || \
			ft_set_env(shell, "PWD", token->args[1]))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
