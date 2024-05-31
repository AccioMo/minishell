/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_priority.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:24:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/31 19:49:14 by mzeggaf          ###   ########.fr       */
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
	while (wait(&shell->exit_code) > 0)
		;
	shell->exit_code >>= 8 & 0x000000ff;
	if (shell->exit_code == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
	return (shell->exit_code);
}

int	ft_redirections_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	// if (!token || (token->type >= REDIR_HEREDOC && token->type <= REDIR_IN))
	// 	if (!token || ft_ambiguous_redirect(token->left, shell))
	// 		return (EXIT_FAILURE);
	if (token->type == REDIR_IN)
	{
		fdin = ft_redir_in_function(token->left);
		return (ft_redirections_token(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_HEREDOC)
	{
		fdin = ft_redir_heredoc_function(token->left);
		return (ft_redirections_token(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_OUT)
	{
		fdout = ft_redir_out_function(token->left);
		return (ft_redirections_token(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_APPEND)
	{
		fdout = ft_redir_append_function(token->left);
		return (ft_redirections_token(token->right, fdin, fdout, shell));
	}
	return (ft_execution_token(token, fdin, fdout, shell));
}

int	ft_pipe_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	int	end[2];

	if (!token)
		return (EXIT_FAILURE);
	if (pipe(end) < 0)
		perror("pipe");
	if (token->type == PIPE)
	{
		ft_redirections_token(token->left, fdin, end[1], shell);
		ft_pipe_token(token->right, end[0], fdout, shell);
		close(end[1]);
		close(end[0]);
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

// int	ft_pipe_function(t_token *token, int fdin, t_shell *shell)
// {
// 	ft_exec_function(token, fdin, end[1], shell);
// 	return (end[0]);
// }
