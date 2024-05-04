/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:41:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/18 18:55:14 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
					return (from[i] = NULL, SUCCESS);
				from[i] = ft_strdup(from[i + 1]);
				if (!from[i])
					return (ERROR);//free l7za9
				free(from[i + 1]);
				i++;
			}
			return (SUCCESS);
		}
		i++;
	}
	return (SUCCESS);
}
//next func to work on...
int	ft_unset(t_cmds *cmds, t_env *env)
{
	int	i;

	i = 1;
	while (cmds->cmd[i])
	{
		if (!ft_getenv(cmds->cmd[i], env->env) && !ft_getenv(cmds->cmd[i], env->vars))
			i++;//jrbt f sh w makatl3 ta chi ERROR so no ERROR managment here
		else
		{
			if (ft_getenv(cmds->cmd[i], env->env))
				ft_delete_env(cmds->cmd[i], env->env);
			if (ft_getenv(cmds->cmd[i], env->vars))
				ft_delete_env(cmds->cmd[i], env->vars);
			i++;
		}
	}
	return (SUCCESS);
}
