/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:24:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/30 17:54:49 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_priority_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == AND)
		ft_and_function(token, fdin, fdout, shell);
	else if (token->type == OR)
		ft_or_function(token, fdin, fdout, shell);
	else
		ft_pipe_token(token, fdin, fdout, shell);
	while (wait(&shell->exit_status) > 0)
		;
	return (shell->exit_status);
}

int	ft_redirections_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == REDIR_IN)
	{
		ft_variables(token->left, shell);
		fdin = ft_redir_in_function(token->left);
		return (ft_redirections_token(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_HEREDOC)
	{
		ft_variables(token->left, shell);
		fdin = ft_redir_heredoc_function(token->left);
		return (ft_redirections_token(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_OUT)
	{
		ft_variables(token->left, shell);
		fdout = ft_redir_out_function(token->left);
		return (ft_redirections_token(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_APPEND)
	{
		ft_variables(token->left, shell);
		fdout = ft_redir_append_function(token->left);
		return (ft_redirections_token(token->right, fdin, fdout, shell));
	}
	return (ft_execution_token(token, fdin, fdout, shell));
}

int	ft_pipe_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	int	fd;

	if (!token)
		return (EXIT_FAILURE);
	if (token->type == PIPE)
	{
		fd = ft_pipe_function(token->left, fdin, shell);
		ft_pipe_token(token->right, fd, fdout, shell);
		return (1);
	}
	return (ft_redirections_token(token, fdin, fdout, shell));
}

int	ft_execution_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == WORD)
		return (ft_exec_function(token, fdin, fdout, shell));
	else if (token->type == SUBSHELL)
		return (ft_priority_token(token->right, fdin, fdout, shell));
	return (EXIT_FAILURE);
}

int	ft_pipe_function(t_token *token, int fdin, t_shell *shell)
{
	int	end[2];

	if (pipe(end) < 0)
		perror("pipe");
	ft_exec_function(token, fdin, end[1], shell);
	close(end[1]);
	return (end[0]);
}
