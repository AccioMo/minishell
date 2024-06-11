/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:15:02 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/11 22:13:58 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_set_env(t_list *env, char *name, char *value)
{
	t_list	*head;

	head = env;
	name = ft_strjoin(name, "=");
	while (env)
	{
		if (!ft_strncmp(env->content, name, ft_strlen(name)))
		{
			free(env->content);
			env->content = ft_strjoin(name, value);
			if (!env->content)
				return (EXIT_FAILURE);
			free(name);
			return (EXIT_SUCCESS);
		}
		env = env->next;
	}
	if (env == NULL)
	{
		name = ft_realloc(name, value);
		if (!name)
			return (EXIT_FAILURE);
		ft_lstadd_back(&head, ft_lstnew(name));
	}
	return (EXIT_SUCCESS);
}

int	ft_first_condition(t_shell *shell)
{
	if (chdir(ft_getenv("HOME", shell->env)) != 0)
	{
		if (ft_getenv("HOME", shell->env) == NULL)
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR);
		else
			ft_perror("");
		return (EXIT_FAILURE);
	}
	if (ft_set_env(shell->env, "OLDPWD", ft_getenv("PWD", shell->env)))
		return (EXIT_FAILURE);
	if (ft_set_env(shell->env, "PWD", ft_getenv("HOME", shell->env)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_second_condition(t_shell *shell, char *pwd)
{
	if (chdir(ft_getenv("OLDPWD", shell->env)) != 0)
	{
		ft_putstr_fd("minishell : cd: ", STDERR);
		ft_putstr_fd(ft_getenv("OLDPWD", shell->env), STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		return (EXIT_FAILURE);
	}
	if (ft_set_env(shell->env, "OLDPWD", ft_getenv("PWD", shell->env)))
		return (EXIT_FAILURE);
	if (ft_set_env(shell->env, "PWD", getcwd(pwd, 255)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_cd_error(char *path, t_shell *shell)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (shell == NULL)
	{
		if (errno == ENOENT)
			ft_putstr_fd("HOME not set\n", 2);
		else if (errno == ENOTDIR)
			ft_putstr_fd("not a directory: ", 2);
		else if (errno == EACCES)
			ft_putstr_fd("permission denied: ", 2);
		else
			ft_putstr_fd(path, 2);
		ft_putstr_fd(path, 2);
		strerror(errno);
		return (EXIT_FAILURE);
	}
	strerror(errno);
	ft_putstr_fd("error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory\n", 2);
	if (path[ft_strlen(path) - 1] != '/')
		path = ft_realloc(ft_strjoin(ft_getenv("PWD", shell->env), "/"), path);
	ft_set_env(shell->env, "PWD", path);
	return (EXIT_FAILURE);
}

int	ft_cd(t_token *token, t_shell *shell)
{
	char	pwd[PATH_MAX];
	char	*path;

	path = token->args[1];
	if (path == NULL && !ft_first_condition(shell))
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
		if (ft_set_env(shell->env, "OLDPWD", ft_getenv("PWD", shell->env)))
			return (EXIT_FAILURE);
		if (ft_set_env(shell->env, "PWD", pwd))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
