/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:20:17 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/12 13:40:43 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_env(t_list *env, int fdout)
{
	int	i;

	i = 0;
	if (!env)
		return (EXIT_SUCCESS);
	while (env)
	{
		if (ft_strchr(env->content, '='))
		{
			ft_putstr_fd(env->content, fdout);
			ft_putchar_fd('\n', fdout);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

static t_list	*ft_create_env(void)
{
	char	pwd[PATH_MAX];
	t_list	*shell_env;

	getcwd(pwd, PATH_MAX);
	shell_env = ft_lstnew(ft_strdup("SHLVL=1"));
	if (!shell_env)
		return (NULL);
	ft_set_env(shell_env, "PWD", pwd);
	ft_set_env(shell_env, "PATH", \
		"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	return (shell_env);
}

t_list	*ft_init_env(char **env)
{
	t_list	*shell_env;
	t_list	*new;
	char	*env_var;
	int		i;

	i = 0;
	if (!env || !env[0])
		return (ft_create_env());
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
