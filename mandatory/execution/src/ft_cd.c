/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:15:02 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/21 23:21:07 by mzeggaf          ###   ########.fr       */
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
	ft_putstr_fd("minishell: cd: ", STDERR);
	perror(str);
	return (EXIT_FAILURE);
}

static char	*ft_path(char *path, char *pwd)
{
	char	*new_path;

	if (path[0] != '/' && pwd[ft_strlen(pwd) - 1] != '/')
	{
		new_path = ft_strjoin(pwd, "/");
		new_path = ft_realloc(new_path, path);
		new_path = ft_realloc(new_path, "/");
		return (new_path);
	}
	return (ft_strjoin(path, "/"));
}

static char	*ft_get_path(char *arg_path, t_shell *shell)
{
	char		pwd[PATH_MAX];
	char		*path;
	struct stat	buf;

	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		ft_putendl_fd(CD_RETRIEVE_ERROR, STDERR);
		path = ft_path(arg_path, ft_getenv("PWD", shell->env));
	}
	else
	{
		path = ft_path(arg_path, pwd);
		if (access(path, R_OK) != 0 || \
			(stat(path, &buf) != -1 && S_ISREG(buf.st_mode)))
		{
			ft_cd_error(arg_path);
			free(path);
			return (NULL);
		}
	}
	return (path);
}

int	ft_cd(t_token *token, t_shell *shell)
{
	char	*path;

	if (!token->args[1])
		return (ft_cd_home(shell));
	path = ft_get_path(token->args[1], shell);
	if (path == NULL)
		return (EXIT_FAILURE);
	else
	{
		(chdir(token->args[1]));
		if (ft_set_env(shell, "OLDPWD", ft_getenv("PWD", shell->env)) || \
			ft_set_env(shell, "PWD", path))
			return (free(path), ft_perror(path, errno));
		return (free(path), EXIT_SUCCESS);
	}
}
