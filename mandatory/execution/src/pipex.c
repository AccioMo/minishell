/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:59:05 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/23 14:00:32 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_dup_pipes(int fdin, int fdout)
{
	if (fdin != 0)
	{
		dup2(fdin, 0);
		close(fdin);
	}
	if (fdout != 1)
	{
		dup2(fdout, 1);
		close(fdout);
	}
}

static void	ft_perror(char *cmd)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": permission denied\n", 2);
	}
	else
		perror(cmd);
}

void	ft_increment_shellvl(t_shell *shell)
{
	char	*shell_lvl;
	int		shell_lvl_int;

	shell_lvl = ft_getenv("SHLVL", shell->env);
	if (!shell_lvl)
		return ;
	shell_lvl_int = ft_atoi(shell_lvl);
	shell_lvl_int++;
	shell_lvl = ft_itoa(shell_lvl_int);
	if (!shell_lvl)
		return ;
	ft_change_env_value(shell, "SHLVL=", shell_lvl);
	free(shell_lvl);
}

int	ft_exec_lines_saver(t_token *token, t_shell *shell, int fdin, int fdout)
{
	char	*cmd_path;
	pid_t	pid;

	cmd_path = ft_allocate_cmd(token->args, shell->env);
	if (!cmd_path)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
	{
		if (fdin < 0)
			exit(EXIT_FAILURE);
		ft_dup_pipes(fdin, fdout);
		execve(cmd_path, token->args, shell->env);
		ft_perror(token->args[0]);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	free(cmd_path);
	return (EXIT_SUCCESS);
}

int	ft_exec_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (ft_expand(token, shell))
		return (EXIT_FAILURE);
	if (ft_have_builtin(token))
		return (ft_execute_builtin(token, fdout, shell));
	if (ft_strncmp(token->args[0], "./minishell\0", 12) == 0)
		ft_increment_shellvl(shell);
	if (ft_exec_lines_saver(token, shell, fdin, fdout))
		return (EXIT_FAILURE);
	if (ft_change_env_value(shell, "_=",
			token->args[ft_two_d_len(token->args) - 1]))
		return (EXIT_FAILURE);
	if (fdin != 0)
		close(fdin);
	if (fdout != 1)
		close(fdout);
	return (0);
}
