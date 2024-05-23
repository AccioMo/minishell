/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:41:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/23 13:44:02 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
//free l7za9
int	ft_delete_env(char *name, char **from)
{
	int	i;

	i = 0;
	while (from[i])
	{
		if (ft_strncmp(from[i], name, ft_strlen(name)) == 0)
		{
			free(from[i]);
			while (from[i])
			{
				if (from[i + 1] == NULL)
					return (from[i] = NULL, EXIT_SUCCESS);
				from[i] = ft_strdup(from[i + 1]);
				if (!from[i])
					return (EXIT_FAILURE);
				free(from[i + 1]);
				i++;
			}
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_unset(t_token *token, t_shell *env)
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
		if (!ft_getenv(token->args[i], env->env))
			i++;
		else
			return (ft_delete_env(token->args[i], env->env));
	}
	return (EXIT_SUCCESS);
}
