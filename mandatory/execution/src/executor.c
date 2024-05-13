/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:24:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/12 20:00:44 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_builtin(t_token *token, t_shell *env)
{
	if (ft_strncmp(token->args[0], "echo", 4) == 0)
		return (ft_echo(token));
	else if (ft_strncmp(token->args[0], "pwd", 3) == 0)
		return (ft_pwd(env));
	else if (ft_strncmp(token->args[0], "cd", 2) == 0)
		return (ft_cd(token, env));
	if (ft_strncmp(token->args[0], "export", 6) == 0)
		return (ft_export(token, env));
	else if (ft_strncmp(token->args[0], "unset", 5) == 0)
		return (ft_unset(token, env));
	return (0);
}

int	ft_execute(t_token *token, t_shell *env)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strncmp(token->args[0], "exit", 4) == 0)
		ft_exit(token, env);
	if (ft_have_builtin(token))
		exit_status = ft_execute_builtin(token, env);
	else
		exit_status = ft_start_pipex(token->args, env->env);
	return (exit_status);
}