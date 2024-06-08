/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:41:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/08 17:41:56 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_delete_env(char *name, t_shell *shell)
{
	t_list	*env;
	t_list	*prev;
	int		len;

	len = ft_strlen(name);
	env = shell->env;
	if (!ft_strncmp(env->content, name, len) && \
		(env->content[len] == '=' || env->content[len] == '\0'))
	{
		shell->env = env->next;
		return (EXIT_SUCCESS);
	}
	while (env)
	{
		if (!ft_strncmp(env->content, name, len) && \
			(env->content[len] == '=' || env->content[len] == '\0'))
		{
			prev->next = env->next;
			ft_lstdelone(env, free);
			return (EXIT_SUCCESS);
		}
		prev = env;
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_unset(t_token *token, t_shell *shell)
{
	int		i;

	i = 1;
	while (token->args[i])
	{
		if (!ft_isalpha(token->args[i][0]))
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(token->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		if (ft_getenv(token->args[i], shell->env))
			ft_delete_env(token->args[i], shell);
		i++;
	}
	return (EXIT_SUCCESS);
}
