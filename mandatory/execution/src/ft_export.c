/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:02:47 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/02 19:40:39 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_print_shell(t_list *env, int fdout)
{
	int	i;
	int	j;

	i = 0;
	while (env)
	{
		j = 0;
		ft_putstr_fd("declare -x ", fdout);
		while (env->content[j] && env->content[j] != '=')
			ft_putchar_fd(env->content[j++], fdout);
		if (env->content[j] == '=')
		{
			ft_putchar_fd('=', fdout);
			ft_putchar_fd('\'', fdout);
			j++;
		}
		while (env->content[j])
			ft_putchar_fd(env->content[j++], fdout);
		ft_putchar_fd('\'', fdout);
		ft_putchar_fd('\n', fdout);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

static int	ft_export_lines_saver(char *new_var, t_list *env)
{
	t_list	*head;

	head = env;
	if (ft_strncmp(new_var, "_\0", 2))
		if (ft_change_env_value(env, "_=", "export"))
			return (EXIT_FAILURE);
	while (env)
	{
		if (!ft_strncmp(env->content, new_var, ft_strlen(new_var)))
		{
			free(env->content);
			env->content = ft_strdup(new_var);
			if (!env->content)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		env = env->next;
	}
	ft_lstadd_back(&head, ft_lstnew(new_var));
	return (EXIT_SUCCESS);
}

static int	ft_var_exist(t_shell *shell, char *var)
{
	char	*var_name;
	char	*var_value;
	int		equal_pos;

	equal_pos = ft_get_index(var, '=');
	var_name = ft_substr(var, 0, equal_pos);
	if (!var_name)
		return(EXIT_FAILURE);
	var_value = ft_getenv(var_name, shell->env);
	if (!var_value)
	{
		free(var_name);
		return(EXIT_FAILURE);
	}
	else
	{
		var_name = ft_strjoin_free(var_name, "=", 1);
		if (ft_change_env_value(shell->env, var_name, ft_strchr(var, '=') + 1))
            return(EXIT_FAILURE);
	}
	free(var_name);
	return (EXIT_SUCCESS);
}

int	ft_export(t_token *token, t_shell *shell, int fdout)
{
	int	j;

	j = 0;
	if (ft_array_len(token->args) == 1)
		return (ft_print_shell(shell->env, fdout));
	while (token->args[++j])
	{
		if (ft_strchr(token->args[j], '=') == NULL)
			return (EXIT_SUCCESS);
		if (ft_isalpha(token->args[j][0]) == 0)
		{
			ft_putstr_fd("export: `", fdout);
			ft_putstr_fd(token->args[1], fdout);
			ft_putstr_fd("': not a valid identifier\n", fdout);
			return (EXIT_FAILURE);
		}
		if (!ft_var_exist(shell, token->args[j]))
			continue ;
		if (ft_export_lines_saver(token->args[j], shell->env))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
