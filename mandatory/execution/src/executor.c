/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:24:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/21 07:06:26 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_define_priority(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == AND)
		return (ft_and_function(token, fdin, fdout, shell));
	else if (token->type == OR)
		return (ft_or_function(token, fdin, fdout, shell));
	return (ft_check_pipe(token, fdin, fdout, shell));
}

int	ft_check_redirections(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == REDIR_IN)
	{
		fdin = ft_redir_in_function(token->left);
		return (ft_check_redirections(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_HEREDOC)
	{
		fdin = ft_redir_heredoc_function(token->left);
		return (ft_check_redirections(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_OUT)
	{
		fdout = ft_redir_out_function(token->left);
		return (ft_check_redirections(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_APPEND)
	{
		fdout = ft_redir_append_function(token->left);
		return (ft_check_redirections(token->right, fdin, fdout, shell));
	}
	return (ft_type_to_execute(token, fdin, fdout, shell));
}

int	ft_check_pipe(t_token *token, int fdin, int fdout, t_shell *shell)
{
	int	fd;

	if (!token)
		return (EXIT_FAILURE);
	if (token->type == PIPE)
	{
		fd = ft_pipe_function(token->left, fdin, shell);
		ft_check_pipe(token->right, fd, fdout, shell);
		return (1);
	}
	return (ft_check_redirections(token, fdin, fdout, shell));
}

int	ft_type_to_execute(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == WORD)
		return (ft_exec_function(token, fdin, fdout, shell));
	else if (token->type == SUBSHELL)
		return (ft_define_priority(token->right, fdin, fdout, shell));
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