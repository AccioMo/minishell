/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:02:47 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/19 17:16:35 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_print_shell(t_shell *env, int fdout)
{
	int	i;
	int	j;

	i = 0;
	while (env->env[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", fdout);
		while (env->env[i][j] && env->env[i][j] != '=')
			ft_putchar_fd(env->env[i][j++], fdout);
		if (env->env[i][j] == '=')
		{
			ft_putchar_fd('=', fdout);
			ft_putchar_fd('\'', fdout);
			j++;
		}
		while (env->env[i][j])
			ft_putchar_fd(env->env[i][j++], fdout);
		ft_putchar_fd('\'', fdout);
		ft_putchar_fd('\n', fdout);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_change_var(char **var)
{
	int	i;
	int	j;
	char	*new_var;

	i = 0;
	j = 0;
	new_var = (char *)malloc(sizeof(char) * (ft_strlen(*var) + 3));
	if (!new_var)
		return (EXIT_FAILURE);
	while ((*var)[i] && (*var)[i] != '=')
		new_var[j++] = (*var)[i++];
	new_var[j++] = '=';
	new_var[j++] = '"';
	while ((*var)[i])
		new_var[j++] = (*var)[i++];
	new_var[j++] = '"';
	new_var[j] = '\0';
	free(*var);
	*var = new_var;
	return (EXIT_SUCCESS);
}

char	**ft_realloc_env(char **env, int size, char *new_var)
{
	char	**new_env;
	int		i;

	i = 0;
	if (ft_count_char(new_var, '=') > 1)
		ft_change_var(&new_var);
	new_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			ft_free(new_env);
			return(NULL);
		}
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	if (!new_env[i])
	{
		ft_free(new_env);
		return (NULL);
	}
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

int	ft_export(t_token *token, t_shell *env, int fdout)
{
	int	i;
	int j;

	j = 1;
	if (ft_two_d_len(token->args) == 1)
		return (ft_print_shell(env, fdout));
	while (token->args[j])
	{
		if (ft_isalpha(token->args[j][0]) == 0 && token->args[j][0] != '_')
		{
			ft_putstr_fd("export: `", fdout);
			ft_putstr_fd(token->args[1], fdout);
			ft_putstr_fd("': not a valid identifier\n", fdout);
			return (EXIT_FAILURE);
		}
		i = 0;
		while (env->env[i])
		{
			if (ft_strncmp(env->env[i], token->args[j], ft_strlen(token->args[j])) == 0)
			{
				free(env->env[i]);
				env->env[i] = ft_strdup(token->args[j]);
				return (EXIT_SUCCESS);
			}
			i++;
		}
		env->env = ft_realloc_env(env->env, ft_two_d_len(env->env) + 1, token->args[j]);
		if (!env->env)
			return (EXIT_FAILURE);
		j++;
	}
	return (EXIT_SUCCESS);
}
