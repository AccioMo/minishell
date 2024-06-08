/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:02:47 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/08 17:45:23 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_print_shell(t_list *env, int fdout)
{
	int	ei;
	int	i;
	int	j;

	i = 0;
	while (env)
	{
		j = 0;
		ft_putstr_fd("declare -x ", fdout);
		ei = ft_index(env->content, '=');
		while (j < ei)
			ft_putchar_fd(env->content[j++], fdout);
		if (env->content[j] == '=')
		{
			ft_putchar_fd('=', fdout);
			ft_putchar_fd('\"', fdout);
			j++;
		}
		while (env->content[j])
			ft_putchar_fd(env->content[j++], fdout);
		ft_putchar_fd('\"', fdout);
		ft_putchar_fd('\n', fdout);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_valid_variable(char *var, int *index)
{
	int	i;

	i = 0;
	if (!var || (!ft_isalpha(var[i]) && var[i] != '_'))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	i++;
	while (var[i] && var[i] != '=' && ft_strncmp(&var[i], "+=", 2))
	{
		if (ft_strchr("+-#?!@*$%^&()[]{}|;:<>,./~", var[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	*index = i;
	return (EXIT_SUCCESS);
}

int	ft_export_variable(char *name, char *var, t_shell *shell)
{
	char	*value;

	value = ft_getenv(name, shell->env);
	if (!ft_strncmp(var, "+=", 2))
	{
		if (value)
			value = ft_strjoin(value, var + 2);
		if (ft_set_env(shell->env, name, value))
			return (EXIT_FAILURE);
	}
	else if (*var == '=')
	{
		if (ft_set_env(shell->env, name, var + 1))
			return (EXIT_FAILURE);
	}
	else
		ft_lstadd_back(&shell->env, ft_lstnew(ft_strdup(name)));
	return (EXIT_SUCCESS);
}

int	ft_export(t_token *token, t_shell *shell, int fdout)
{
	char	*name;
	int		status;
	int		j;
	int		i;

	j = 1;
	status = 0;
	if (ft_array_len(token->args) == 1)
		return (ft_print_shell(shell->env, fdout));
	while (token->args[j])
	{
		if (ft_valid_variable(token->args[j], &i))
			status = EXIT_FAILURE;
		else
		{
			name = ft_substr(token->args[j], 0, i);
			if (ft_export_variable(name, &token->args[j][i], shell))
				return (EXIT_FAILURE);
		}
		j++;
	}
	return (status);
}
