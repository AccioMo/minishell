/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:02:47 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/18 18:59:10 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->env[i])
	{
		ft_putstr_fd(env->env[i], STDOUT);
		ft_putchar_fd('\n', STDOUT);
		i++;
	}
	return (SUCCESS);
}

char	**ft_realloc_env(char **env, int size, char *new_var)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i-- >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	if (!new_env[i])
	{
		while (i-- >= 0)
			free(new_env[i]);
		free(new_env);
		return (NULL);
	}
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

int	ft_export(t_cmds *cmd, t_env *env)
{
	int	i;
	int j;

	j = 1;
	if (ft_two_d_len(cmd->cmd) == 1)
		return (ft_print_env(env));
	while (cmd->cmd[j])
	{
		i = 0;
		while (env->env[i])
		{
			if (ft_strncmp(env->env[i], cmd->cmd[j], ft_strlen(cmd->cmd[j])) == 0)
			{
				free(env->env[i]);
				env->env[i] = ft_strdup(cmd->cmd[j]);
				return (SUCCESS);
			}
			i++;
		}
		env->env = ft_realloc_env(env->env, ft_two_d_len(env->env) + 1, cmd->cmd[j]);
		if (!env->env)
			return (ERROR);
		j++;
	}
	return (SUCCESS);
}
