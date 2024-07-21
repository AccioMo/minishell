/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:15:02 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/21 19:25:45 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	ft_cd_home(t_shell *shell)
{
	char	*home;

	home = ft_getenv("HOME", shell->env);
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR);
		return (EXIT_FAILURE);
	}
	if (chdir(home) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR);
		ft_putstr_fd(home, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		return (EXIT_FAILURE);
	}
	if (ft_set_env(shell, "OLDPWD", ft_getenv("PWD", shell->env)))
		return (EXIT_FAILURE);
	if (ft_set_env(shell, "PWD", home))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_cd_error(char *str)
{
	perror(str);
	free(str);
	return (EXIT_FAILURE);
}

static char	*ft_path(char *path, char *pwd)
{
	char	*new_path;

	if (path[0] != '/' && pwd[ft_strlen(pwd) - 1] != '/')
	{
		pwd = ft_strjoin(pwd, "/");
		if (!pwd)
			return (NULL);
	}
	else
		pwd = ft_strdup(pwd);
	new_path = ft_realloc(pwd, path);
	return (new_path);
}

int	ft_cd(t_token *token, t_shell *shell)
{
	char	pwd[PATH_MAX];
	char	*og_path;
	char	*path;

	if (!token->args[1])
		return (ft_cd_home(shell));
	og_path = ft_strjoin("minishell: cd: ", token->args[1]);
	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		og_path = ft_strdup(CD_RETRIEVE_ERROR);
		path = ft_path(token->args[1], ft_getenv("PWD", shell->env));
	}
	else
		path = ft_path(token->args[1], pwd);
	if (path == NULL)
		return (EXIT_FAILURE);
	else
	{
		if (chdir(token->args[1]) != 0)
			ft_cd_error(og_path);
		if (ft_set_env(shell, "OLDPWD", ft_getenv("PWD", shell->env)) || \
			ft_set_env(shell, "PWD", path))
			return (free(path), ft_perror(path, errno));
		return (free(path), EXIT_SUCCESS);
	}
}
