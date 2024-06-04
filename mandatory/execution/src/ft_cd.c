/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:15:02 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/04 05:25:37 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_change_env_value(t_list *env, char *name, char *value)
{
	while (env)
	{
		if (!ft_strncmp(env->content, name, ft_strlen(name)))
		{
			free(env->content);
			env->content = ft_strjoin(name, value);
			return (EXIT_SUCCESS);
		}
		env = env->next;
	}
	if (env == NULL)
	{
		name = ft_strjoin(name, value);
		if (!name)
			return (EXIT_FAILURE);
		env = ft_lstnew(name);
	}
	return (EXIT_SUCCESS);
}

static char	*ft_get_path(char **args, t_list *env)
{
	char	*path;

	if (ft_strncmp(args[1], "/", 1) == 0)
		path = args[1];
	else if (ft_strncmp(args[1], "~/", 2) == 0)
		path = ft_strjoin(ft_getenv("HOME", env), &args[1][1]);
	else if (ft_strncmp(args[1], "~", 1) == 0)
		path = ft_realloc(ft_strjoin(ft_getenv("HOME", env), "/"), &args[1][1]);
	else
		path = ft_realloc(ft_strjoin(ft_getenv("PWD", env), "/"), args[1]);
	return (path);
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
	if (ft_change_env_value(shell->env, "OLDPWD=",
			ft_getenv("PWD", shell->env)))
		return (EXIT_FAILURE);
	if (ft_change_env_value(shell->env, "PWD=",
			ft_getenv("HOME", shell->env)))
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
	if (ft_change_env_value(shell->env, "OLDPWD=",
			ft_getenv("PWD", shell->env)))
		return (EXIT_FAILURE);
	if (ft_change_env_value(shell->env, "PWD=", getcwd(pwd, 255)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_token *token, t_shell *shell)
{
	char	pwd[255];
	char	*path;

	path = ft_get_path(token->args, shell->env);
	if (!path)
		return (EXIT_FAILURE);
	if (token->args[1] == NULL && !ft_first_condition(shell))
		return (EXIT_SUCCESS);
	else if (token->args[1] == NULL)
		return (EXIT_FAILURE);
	else if (!ft_strncmp(token->args[1], "-\0", 2))
		return (ft_second_condition(shell, pwd));
	else if (ft_dir_exists(path, shell))
		return (EXIT_FAILURE);
	else
	{
		if (chdir(path) != 0)
			ft_perror(path);
		if (ft_change_env_value(shell->env, "OLDPWD=",
				ft_getenv("PWD", shell->env)))
			return (EXIT_FAILURE);
		if (ft_change_env_value(shell->env, "PWD=", getcwd(pwd, 255)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
