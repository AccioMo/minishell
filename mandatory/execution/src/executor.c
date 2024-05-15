/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:24:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/15 21:17:18 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_define_priority(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == AND)
		return (ft_and_function(token, fdin, fdout, shell));
	else if (token->type == OR)
		return (ft_or_function(token, fdin, fdout, shell));
	return (ft_check_redirections(token, fdin, fdout, shell));
}

int	ft_check_redirections(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == REDIR_IN)
	{
		fdin = redir_in_function(token->left, shell);
		return (ft_check_redirections(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_HEREDOC)
	{
		fdin = redir_heredoc_function(token->left, shell);
		return (ft_check_redirections(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_OUT)
	{
		fdout = redir_out_function(token->left, shell);
		return (ft_check_redirections(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_APPEND)
	{
		fdout = redir_append_function(token->left, shell);
		return (ft_check_redirections(token->right, fdin, fdout, shell));
	}
	return (ft_check_pipe(token, fdin, fdout, shell));
}

int	ft_check_pipe(t_token *token, int fdin, int fdout, t_shell *shell)
{
	int	fd;

	if (!token)
		return (EXIT_FAILURE);
	if (token->type == PIPE)
	{
		fd = pipe_function(token->left, fdin, fdout, shell);
		ft_check_pipe(token->right, fd, fdout, shell);
		return (1);
	}
	return (ft_type_to_execute(token, fdin, fdout, shell));
}

int	ft_type_to_execute(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == WORD)
		return (exec_function(token, fdin, fdout, shell));
	else if (token->type == SUBSHELL)
		return (ft_define_priority(token->right, fdin, fdout, shell));
	return (EXIT_FAILURE);
}

// int	ft_execute_builtin(t_token *token, t_shell *env)
// {
// 	if (ft_strncmp(token->args[0], "echo", 4) == 0)
// 		return (ft_echo(token));
// 	else if (ft_strncmp(token->args[0], "pwd", 3) == 0)
// 		return (ft_pwd(env));
// 	else if (ft_strncmp(token->args[0], "cd", 2) == 0)
// 		return (ft_cd(token, env));
// 	if (ft_strncmp(token->args[0], "export", 6) == 0)
// 		return (ft_export(token, env));
// 	else if (ft_strncmp(token->args[0], "unset", 5) == 0)
// 		return (ft_unset(token, env));
// 	return (0);
// }

// int	ft_execute(t_token *token, t_shell *env)
// {
// 	int	exit_status;
// 	if (ft_strncmp(token->args[0], "exit", 4) == 0)
// 		ft_exit(token, env);
// 	if (ft_have_builtin(token))
// 		exit_status = ft_execute_builtin(token, env);
// 	else
// 		exit_status = ft_start_pipex(token->args, env->env);
// 	return (exit_status);
// }