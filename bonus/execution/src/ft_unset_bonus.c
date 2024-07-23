/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:41:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/23 02:30:44 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"

static int	ft_match_variable(char *name, t_list *env)
{
	int		len;

	len = ft_strlen(name);
	if (!ft_strncmp(env->content, name, len))
		if ((env->content[len] == '=' || env->content[len] == '\0'))
			return (1);
	return (0);
}

static int	ft_delete_env(char *name, t_shell *shell)
{
	t_list	*env;
	t_list	*tmp_env;

	env = shell->env;
	if (ft_match_variable(name, env))
	{
		shell->env = env->next;
		ft_lstdelone(env, free);
		return (EXIT_SUCCESS);
	}
	while (env)
	{
		if (ft_match_variable(name, env))
		{
			tmp_env->next = env->next;
			ft_lstdelone(env, free);
			return (EXIT_SUCCESS);
		}
		tmp_env = env;
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

static int	ft_valid_unset(char *name)
{
	int	i;

	i = 0;
	if (!name || (!ft_isalpha(name[i]) && name[i] != '_'))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	i++;
	while (name[i])
	{
		if (ft_strchr("+-#?!@*$%^&()[]{}|;:<>,./~\'\"", name[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_unset(t_token *token, t_shell *shell)
{
	int		i;

	i = 1;
	while (token->args[i])
	{
		if (ft_valid_unset(token->args[i]))
			return (EXIT_FAILURE);
		if (ft_getenv(token->args[i], shell->env))
			ft_delete_env(token->args[i], shell);
		i++;
	}
	return (EXIT_SUCCESS);
}
