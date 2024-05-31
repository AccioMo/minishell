/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:15:02 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/31 17:12:10 by mzeggaf          ###   ########.fr       */
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

int	ft_dir_exists(t_token *token)
{
	struct stat	statbuf;

	if (stat(token->args[1], &statbuf) != 0)
	{
		if (errno == ENOENT)
		{
			ft_putstr_fd("minishell: cd: ", STDERR);
			ft_putstr_fd(token->args[1], STDERR);
			ft_putstr_fd(": No such file or directory\n", STDERR);
			return (EXIT_FAILURE);
		}
		else
		{
			perror("stat");
			return (EXIT_FAILURE);
		}
	}
	return (!(S_ISDIR(statbuf.st_mode)));
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
	if (ft_change_env_value(shell->env, "OLDPWD=", ft_getenv("PWD", shell->env)))
		return (EXIT_FAILURE);
	if (ft_change_env_value(shell->env, "PWD=", ft_getenv("HOME", shell->env)))
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
	if (ft_change_env_value(shell->env, "OLDPWD=", ft_getenv("PWD", shell->env)))
		return (EXIT_FAILURE);
	if (ft_change_env_value(shell->env, "PWD=", getcwd(pwd, 255)))
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
	else if (ft_dir_exists(token))
		return (EXIT_FAILURE);
	else
	{
		if (chdir(token->args[1]) != 0)
			ft_perror(token->args[1]);
		if (ft_change_env_value(shell->env, "OLDPWD=", ft_getenv("PWD", shell->env)))
			return (EXIT_FAILURE);
		if (ft_change_env_value(shell->env, "PWD=", getcwd(pwd, 255)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
