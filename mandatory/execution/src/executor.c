/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:24:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/18 18:40:51 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_builtin(t_cmds *cmd, t_env *env)
{
	if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
		return (ft_echo(cmd));
	else if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
		return (ft_pwd(env));
	else if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
		return (ft_cd(cmd, env));
	if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
		return (ft_export(cmd, env));
	else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)//to add later
		return (ft_unset(cmd, env));
	return (0);
}

int	ft_execute(t_cmds *cmd, t_env *env)
{
	if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
		ft_exit(cmd, env);
	if (ft_have_builtin(cmd))
		cmd->exit_status = ft_execute_builtin(cmd, env);
	else
		cmd->exit_status = ft_start_pipex(cmd->cmd, env->env);
	return (cmd->exit_status);
}