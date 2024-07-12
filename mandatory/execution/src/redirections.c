/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:15:21 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/07/12 12:43:20 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_redir_in_function(t_token *token)
{
	int	fd;

	fd = open(token->args[0], O_RDONLY);
	if (fd < 0)
	{
		perror(token->args[0]);
		return (-1);
	}
	return (fd);
}

int	ft_redir_out_function(t_token *token)
{
	int	fd;

	fd = open(token->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(token->args[0]);
		return (-1);
	}
	return (fd);
}

int	ft_redir_append_function(t_token *token)
{
	int	fd;

	fd = open(token->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(token->args[0]);
		return (-1);
	}
	return (fd);
}

int	ft_handle_redirs_in(t_token *token, int fdin[2], int fdout, t_shell *shell)
{
	int	status;
	int	fdin_backup;

	if (token->type == REDIR_IN)
		fdin[0] = ft_redir_in_function(token->left);
	else if (token->type == REDIR_HEREDOC)
		fdin[0] = ft_redir_heredoc_function(token->left, shell);
	fdin_backup = fdin[0];
	if (!token->right)
	{
		ft_close_fds(fdin_backup, fdout);
		return (EXIT_SUCCESS);
	}
	status = ft_redir_token(token->right, fdin, fdout, shell);
	close(fdin_backup);
	return (status);
}

int	ft_handle_redirs_out(t_token *token, int fdin[2], int fdout, t_shell *shell)
{
	int	status;

	if (token->type == REDIR_OUT)
		fdout = ft_redir_out_function(token->left);
	else if (token->type == REDIR_APPEND)
		fdout = ft_redir_append_function(token->left);
	if (!token->right)
	{
		ft_close_fds(fdin[0], fdout);
		return (EXIT_SUCCESS);
	}
	status = ft_redir_token(token->right, fdin, fdout, shell);
	close(fdout);
	return (status);
}
