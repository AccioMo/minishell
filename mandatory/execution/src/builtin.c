/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:18:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/10 21:43:56 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_is_builtin(t_token *token)
{
	if (ft_strncmp(token->args[0], "echo\0", 5) == 0)
		return (true);
	if (ft_strncmp(token->args[0], "pwd\0", 4) == 0)
		return (true);
	if (ft_strncmp(token->args[0], "cd\0", 3) == 0)
		return (true);
	if (ft_strncmp(token->args[0], "unset\0", 6) == 0)
		return (true);
	if (ft_strncmp(token->args[0], "export\0", 7) == 0)
		return (true);
	if (ft_strncmp(token->args[0], "env\0", 4) == 0)
		return (true);
	if (ft_strncmp(token->args[0], "exit\0", 5) == 0)
		return (true);
	return (false);
}

int	ft_execute_builtin(t_token *token, int fdout, t_shell *shell)
{
	if (ft_set_env(shell->env, "_",
			token->args[ft_array_len(token->args) - 1]))
		return (EXIT_FAILURE);
	if (ft_strncmp(token->args[0], "echo\0", 5) == 0)
		shell->exit_code = set_exit_code(ft_echo(token, fdout), true);
	else if (ft_strncmp(token->args[0], "pwd\0", 4) == 0)
		shell->exit_code = set_exit_code(ft_pwd(fdout, shell->env), true);
	else if (ft_strncmp(token->args[0], "cd\0", 3) == 0)
		shell->exit_code = set_exit_code(ft_cd(token, shell), true);
	if (ft_strncmp(token->args[0], "export\0", 7) == 0)
		shell->exit_code = set_exit_code(ft_export(token, shell, fdout), true);
	else if (ft_strncmp(token->args[0], "unset\0", 6) == 0)
		shell->exit_code = set_exit_code(ft_unset(token, shell), true);
	else if (ft_strncmp(token->args[0], "env\0", 4) == 0)
		shell->exit_code = set_exit_code(ft_env(shell->env, fdout), true);
	else if (ft_strncmp(token->args[0], "exit\0", 5) == 0)
		shell->exit_code = set_exit_code(ft_exit(token, shell), true);
	return (shell->exit_code);
}

char	*ft_path(char *path, t_shell *shell)
{
	char	*new_path;

	if (path[0] != '/')
	{
		new_path = ft_strjoin(ft_getenv("PWD", shell->env), "/");
		new_path = ft_realloc(new_path, path);
		if (!new_path)
			return (NULL);
		free(path);
		return (new_path);
	}
	return (path);
}
