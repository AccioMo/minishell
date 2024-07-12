/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:18:51 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/12 13:40:32 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_run_checks(char *cmd_path, char *cmd)
{
	struct stat	buf;

	if (stat(cmd_path, &buf) == -1)
		exit(ft_exec_error(cmd, errno));
	if (S_ISDIR(buf.st_mode))
		exit(ft_exec_error(cmd, EISDIR));
	if (access(cmd_path, X_OK) == -1)
		exit(ft_exec_error(cmd, EACCES));
}

void	sigquit_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
	}
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
	}
}

int	ft_execution_process(t_token *token, int fdin[2], int fdout, t_shell *shell)
{
	char	**env_array;
	char	*cmd_path;

	shell->last_pid = fork();
	if (shell->last_pid == 0)
	{
		if (fdin[0] < 0 || fdout < 0)
			exit(EXIT_FAILURE);
		ft_dup_pipes(fdin, fdout);
		env_array = ft_list_to_array(shell->env);
		cmd_path = ft_allocate_cmd(token->args, env_array);
		if (!cmd_path)
			exit(127);
		ft_run_checks(cmd_path, token->args[0]);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(cmd_path, token->args, env_array);
		perror(token->args[0]);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	else if (shell->last_pid < 0)
		ft_perror("fork", errno);
	return (shell->last_pid);
}

int	ft_handle_dots(t_token *token)
{
	if (ft_strncmp(token->args[0], ".\0", 2) == 0)
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		return (2);
	}
	else
	{
		ft_putstr_fd("minishell: ..: command not found\n", 2);
		return (127);
	}
}

int	ft_exec_function(t_token *token, int fdin[2], int fdout, t_shell *shell)
{
	char	*last_cmd;
	int		pid;

	if (!token || token->args == NULL || ft_expand_variables(token, shell) \
		|| ft_expand_wildcard(token) || token->args == NULL)
		return (EXIT_FAILURE);
	if (!token->args[0])
		return (EXIT_SUCCESS);
	if (ft_strncmp(token->args[0], ".\0", 2) == 0 || \
		ft_strncmp(token->args[0], "..\0", 3) == 0)
		return (ft_handle_dots(token));
	if (ft_is_builtin(token))
		return (ft_execute_builtin(token, fdout, shell));
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = ft_execution_process(token, fdin, fdout, shell);
	if (pid < 0)
		return (2);
	last_cmd = token->args[ft_array_len(token->args) - 1];
	if (ft_set_env(shell->env, "_", last_cmd))
		return (EXIT_FAILURE);
	return (0);
}
