/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:18:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/31 19:42:57 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_is_builtin(t_token *token)
{
	if (ft_strncmp(token->args[0], "echo\0", 5) == 0)
		return (TRUE);
	if (ft_strncmp(token->args[0], "pwd\0", 4) == 0)
		return (TRUE);
	if (ft_strncmp(token->args[0], "cd\0", 3) == 0)
		return (TRUE);
	if (ft_strncmp(token->args[0], "unset\0", 6) == 0)
		return (TRUE);
	if (ft_strncmp(token->args[0], "export\0", 7) == 0)
		return (TRUE);
	if (ft_strncmp(token->args[0], "env\0", 4) == 0)
		return (TRUE);
	if (ft_strncmp(token->args[0], "exit\0", 5) == 0)
		return (TRUE);
	return (FALSE);
}

int	ft_execute_builtin(t_token *token, int fdout, t_shell *shell)
{
	if (ft_change_env_value(shell->env, "_=",
			token->args[ft_array_len(token->args) - 1]))
		return (EXIT_FAILURE);
	if (ft_strncmp(token->args[0], "echo\0", 5) == 0)
		return (ft_echo(token, fdout));
	else if (ft_strncmp(token->args[0], "pwd\0", 4) == 0)
		return (ft_pwd(fdout, shell->env));
	else if (ft_strncmp(token->args[0], "cd\0", 3) == 0)
		return (ft_cd(token, shell));
	if (ft_strncmp(token->args[0], "export\0", 7) == 0)
		return (ft_export(token, shell, fdout));
	else if (ft_strncmp(token->args[0], "unset\0", 6) == 0)
		return (ft_unset(token, shell->env));
	else if (ft_strncmp(token->args[0], "env\0", 4) == 0)
		return (ft_env(shell->env, fdout));
	else if (ft_strncmp(token->args[0], "exit\0", 5) == 0)
		ft_exit(token, shell);
	return (0);
}
