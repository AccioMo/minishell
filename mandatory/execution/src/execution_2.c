/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:18:51 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/08 17:00:05 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_exec_error(char *cmd, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (code == ENOENT)
	{
		ft_putstr_fd("command not found\n", 2);
		return (127);
	}
	else if (code == EACCES)
	{
		ft_putstr_fd("permission denied\n", 2);
		return (126);
	}
	else if (code == EISDIR)
	{
		ft_putstr_fd("is a directory\n", 2);
		return (126);
	}
	else
		ft_putstr_fd(strerror(code), 2);
	return (1);
}

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

int	ft_execution_process(t_token *token, int fdin, int fdout, t_shell *shell)
{
	char	**env_array;
	char	*cmd_path;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (fdin < 0)
			exit(EXIT_FAILURE);
		ft_dup_pipes(fdin, fdout);
		env_array = ft_list_to_array(shell->env);
		cmd_path = ft_allocate_cmd(token->args, env_array);
		if (!cmd_path)
			exit(ft_exec_error(token->args[0], 127));
		ft_run_checks(cmd_path, token->args[0]);
		execve(cmd_path, token->args, env_array);
		ft_perror(token->args[0]);
		free(cmd_path);
		ft_perror(token->args[0]);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		ft_perror("fork");
	shell->last_pid = pid;
	return (pid);
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

int	ft_exec_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	char	*last_cmd;
	int		pid;

	if (!token || token->args == NULL)
		return (EXIT_FAILURE);
	if (ft_expand_variables(token, shell) || ft_expand_wildcard(token) \
		|| token->args == NULL)
		return (EXIT_FAILURE);
	if (!token->args[0])
		return (EXIT_SUCCESS);
	if (ft_strncmp(token->args[0], ".\0", 2) == 0 || \
		ft_strncmp(token->args[0], "..\0", 3) == 0)
		return (ft_handle_dots(token));
	if (ft_is_builtin(token))
		return (ft_execute_builtin(token, fdout, shell));
	if (ft_strncmp(token->args[0], "./minishell\0", 12) == 0)
		ft_increment_shellvl(shell);
	pid = ft_execution_process(token, fdin, fdout, shell);
	if (pid < 0)
		return (2);
	last_cmd = token->args[ft_array_len(token->args) - 1];
	if (ft_set_env(shell->env, "_", last_cmd))
		return (EXIT_FAILURE);
	return (0);
}

void	ft_close_fds(int fdin, int fdout)
{
	if (fdin != 0)
		close(fdin);
	if (fdout != 1)
		close(fdout);
}
