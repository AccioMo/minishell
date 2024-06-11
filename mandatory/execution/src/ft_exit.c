/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:41:57 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/11 22:52:31 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (!ft_larger_than(str, "9223372036854775807"))
		return (0);
	return (1);
}

int	ft_exit(t_token *token, t_shell *shell)
{
	int	exit_code;

	exit_code = shell->exit_code;
	if (token->args[1] && !ft_is_number(token->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(token->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code = 255;
	}
	else if (token->args[1])
	{
		exit_code = ft_atoi(token->args[1]);
		if (ft_array_len(token->args) > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (EXIT_FAILURE);
		}
	}
	if (shell->subshell)
		return (shell->exit_code);
	ft_free_tree(shell->root);
	ft_lstclear(&shell->env, free);
	shell->root = NULL;
	return (exit_code);
}
