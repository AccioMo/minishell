/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:18:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/25 18:35:34 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_check_env(t_shell *shell, char *name)
{
	t_list	*tmp;
	char	*tmp_str;

	tmp = shell->env;
	while (tmp)
	{
		tmp_str = tmp->content;
		if (ft_strncmp(tmp_str, name, ft_strlen(name)) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(name);
			return ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		ft_lstadd_back(&shell->env, ft_lstnew(ft_strdup(name)));
}

int	ft_is_builtin(t_token *token)
{
	if (token->args[0] == NULL || !token->args || token == NULL)
		return (false);
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

static int	ft_execute_builtin(t_token *token, int fdout, t_shell *shell)
{
	if (ft_strncmp(token->args[0], "echo\0", 5) == 0)
		shell->exit_code = set_exit_code(ft_echo(token, fdout), true);
	else if (ft_strncmp(token->args[0], "pwd\0", 4) == 0)
		shell->exit_code = set_exit_code(ft_pwd(fdout, shell), true);
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

int	ft_builtin_process(t_token *token, int fdout, t_shell *shell)
{
	if (ft_set_env(shell, "_",
			token->args[ft_array_len(token->args) - 1]))
		return (EXIT_FAILURE);
	if (shell->subshell)
	{
		shell->last_pid = fork();
		if (shell->last_pid < 0)
			return (ft_perror("fork", errno));
		else if (shell->last_pid == 0)
			exit(ft_execute_builtin(token, fdout, shell));
		return (EXIT_SUCCESS);
	}
	return (ft_execute_builtin(token, fdout, shell));
}
