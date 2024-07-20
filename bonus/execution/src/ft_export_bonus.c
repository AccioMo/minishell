/* ************************************************************************** */
/*		                                                                      */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:02:47 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/09 16:03:04 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"

static char	**ft_sort_env(t_list *env)
{
	char	**arr;
	int		i;

	i = 0;
	arr = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!arr)
		return (NULL);
	while (env)
	{
		arr[i] = ft_strdup(env->content);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	sort_arr(arr);
	return (arr);
}

static int	ft_print_shell(t_list *env, int fdout)
{
	char	**arr;
	int		i;
	int		j;

	i = -1;
	arr = ft_sort_env(env);
	while (arr && arr[++i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", fdout);
		while (arr[i][j] != '=' && arr[i][j])
			ft_putchar_fd(arr[i][j++], fdout);
		if (arr[i][j] == '=')
		{
			ft_putchar_fd('=', fdout);
			ft_putchar_fd('\"', fdout);
			j++;
			while (arr[i][j])
				ft_putchar_fd(arr[i][j++], fdout);
			ft_putchar_fd('\"', fdout);
		}
		ft_putchar_fd('\n', fdout);
	}
	return (ft_free(arr), EXIT_SUCCESS);
}

static int	ft_valid_variable(char *var, int *index)
{
	int	i;

	i = 0;
	if (!var || (!ft_isalpha(var[i]) && var[i] != '_'))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	i++;
	while (var[i] && var[i] != '=' && ft_strncmp(&var[i], "+=", 2))
	{
		if (ft_strchr("+-#?!@*$%^&()[]{}|;:<>,./~", var[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	*index = i;
	return (EXIT_SUCCESS);
}

static int	ft_export_variable(char *name, char *var, t_shell *shell)
{
	char	*value;

	if (!ft_strncmp(var, "+=", 2))
	{
		if (ft_getenv(name, shell->env))
			value = ft_strjoin(ft_getenv(name, shell->env), var + 2);
		else
			value = ft_strdup(var + 2);
		if (ft_set_env(shell, name, value))
		{
			free(value);
			return (EXIT_FAILURE);
		}
		free(value);
	}
	else if (*var == '=')
	{
		if (!shell->env)
			shell->env = ft_lstnew(ft_strjoin(name, var));
		else if (ft_set_env(shell, name, var + 1))
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
				return (free(name), EXIT_FAILURE);
			free(name);
		}
		j++;
	}
	return (status);
}
