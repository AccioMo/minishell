/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:20:17 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/23 02:30:44 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"

static int	ft_set_env_2(t_list *env, char *name, char *value)
{
	t_list	*head;

	head = env;
	while (env)
	{
		if (!ft_strncmp(env->content, name, ft_strlen(name)))
		{
			free(env->content);
			env->content = ft_realloc(name, value);
			if (!env->content)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		env = env->next;
	}
	if (!env)
	{
		name = ft_realloc(name, value);
		if (!name)
			return (EXIT_FAILURE);
		ft_lstadd_back(&head, ft_lstnew(name));
	}
	return (EXIT_SUCCESS);
}

int	ft_set_env(t_shell *shell, char *name, char *value)
{
	t_list	*env;

	env = shell->env;
	name = ft_strjoin(name, "=");
	if (!env)
	{
		name = ft_strjoin(name, value);
		if (!name)
			return (EXIT_FAILURE);
		shell->env = ft_lstnew(name);
		return (EXIT_SUCCESS);
	}
	return (ft_set_env_2(env, name, value));
}

int	ft_env(t_list *env, int fdout)
{
	int	i;

	i = 0;
	if (!env)
		return (EXIT_SUCCESS);
	while (env)
	{
		if (!ft_strncmp(env->content, "_=", 2))
		{
			ft_putstr_fd("_=/usr/bin/env", fdout);
			ft_putchar_fd('\n', fdout);
		}
		else if (ft_strchr(env->content, '='))
		{
			ft_putstr_fd(env->content, fdout);
			ft_putchar_fd('\n', fdout);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

static t_list	*ft_create_env(t_shell *shell)
{
	char	pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	shell->env = ft_lstnew(ft_strdup("SHLVL=1"));
	if (!shell->env)
		return (NULL);
	ft_set_env(shell, "PWD", pwd);
	ft_set_env(shell, "PATH", \
		"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	return (shell->env);
}

t_list	*ft_init_env(char **env, t_shell *shell)
{
	t_list	*shell_env;
	t_list	*new;
	char	*env_var;
	int		i;

	i = 0;
	if (!env || !env[0])
		return (ft_create_env(shell));
	env_var = ft_strdup(env[i++]);
	if (!env_var)
		return (NULL);
	shell_env = ft_lstnew(env_var);
	if (!shell_env)
		return (NULL);
	while (env[i])
	{
		env_var = ft_strdup(env[i]);
		new = ft_lstnew(env_var);
		if (!new)
			return (NULL);
		ft_lstadd_back(&shell_env, new);
		i++;
	}
	return (shell_env);
}
