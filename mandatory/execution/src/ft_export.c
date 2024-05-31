/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:02:47 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/31 17:36:22 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// int	ft_change_existing_var(t_shell *shell, char *var)
// {
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = ft_substr(var, 0, ft_index(var, '=') + 1);
// 	if (!tmp)
// 		return (EXIT_FAILURE);
// 	if (ft_change_env_value(shell->env, tmp, ft_strchr(var, '=') + 1))
// 	{
// 		free(tmp);
// 		return (EXIT_SUCCESS);
// 	}
// 	free(tmp);
// 	return (EXIT_FAILURE);
// }

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
	char	*tmp;
	int		i;
	int		equal_pos;

	i = 0;
	equal_pos = ft_get_index(var, '=');
	if (equal_pos <= 0)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	tmp = ft_substr(var, 0, ft_get_index(var, '='));
	if (!tmp)
		return (EXIT_FAILURE);
	if (ft_getenv(tmp, shell->env))
	{
		free(tmp);
		// if (ft_change_existing_var(shell, var) == EXIT_FAILURE)
		// 	return (EXIT_FAILURE);
		return (1);
	}
	free(tmp);
	return (0);
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
			token->args[j] = ft_strjoin_free(token->args[j], "=", 0);
		if (ft_var_exist(shell, token->args[j]))
			continue ;
		if (ft_isalpha(token->args[j][0]) == 0)
		{
			ft_putstr_fd("export: `", fdout);
			ft_putstr_fd(token->args[1], fdout);
			ft_putstr_fd("': not a valid identifier\n", fdout);
			return (EXIT_FAILURE);
		}
		if (ft_export_lines_saver(token->args[j], shell->env))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
