/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:41:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/30 20:30:25 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_delete_env(char *name, t_list *env)
{
	t_list	*tmp;

	while (env)
	{
		if (ft_strncmp(env->content, name, ft_strlen(name)) == 0)
		{
			tmp = env->next->next;
			ft_lstdelone(env, free);
			env->next = tmp;
			return (EXIT_SUCCESS);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_unset(t_token *token, t_list *env)
{
	int	i;

	i = 1;
	while (token->args[i])
	{
		if (!ft_isalpha(token->args[i][0]))
		{
			ft_putstr_fd("unset: `", STDERR_FILENO);
			ft_putstr_fd(token->args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		if (!ft_getenv(token->args[i], env))
			i++;
		else
			return (ft_delete_env(token->args[i], env));
	}
	return (EXIT_SUCCESS);
}
