/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_draft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:24:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/16 20:38:46 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	stage_one_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == AND)
		return (and_function(token, fdin, fdout, shell));
	else if (token->type == OR)
		return (or_function(token, fdin, fdout, shell));
	return (stage_two_function(token, fdin, fdout, shell));
}

int	stage_three_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == REDIR_IN)
	{
		fdin = redir_in_function(token->left, shell);
		return (stage_three_function(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_HEREDOC)
	{
		fdin = redir_heredoc_function(token->left, shell);
		return (stage_three_function(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_OUT)
	{
		fdout = redir_out_function(token->left, shell);
		return (stage_three_function(token->right, fdin, fdout, shell));
	}
	else if (token->type == REDIR_APPEND)
	{
		fdout = redir_append_function(token->left, shell);
		return (stage_three_function(token->right, fdin, fdout, shell));
	}
	return (stage_four_function(token, fdin, fdout, shell));
}

int	stage_two_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	int	fd;

	if (!token)
		return (EXIT_FAILURE);
	if (token->type == PIPE)
	{
		fd = pipe_function(token->left, fdin, fdout, shell);
		stage_two_function(token->right, fd, fdout, shell);
		return (1);
	}
	return (stage_three_function(token, fdin, fdout, shell));
}

int	stage_four_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == WORD)
		return (exec_function(token, fdin, fdout, shell));
	else if (token->type == SUBSHELL)
		return (stage_one_function(token->right, fdin, fdout, shell));
	return (EXIT_FAILURE);
}

int	redir_in_function(t_token *token, t_shell *shell)
{
	int	fd;

	fd = open(token->args[0], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

int	redir_out_function(t_token *token, t_shell *shell)
{
	int	fd;

	fd = open(token->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

int	redir_append_function(t_token *token, t_shell *shell)
{
	int	fd;

	fd = open(token->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

int	redir_heredoc_function(t_token *token, t_shell *shell)
{
	int	fd;

	// fd = open(token->args[0], O_RDONLY);
	// if (fd < 0)
	// {
	// 	perror("open");
	// 	return (-1);
	// }
	return (0);
}

int	and_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (stage_two_function(token->left, fdin, fdout, shell))
		return (stage_one_function(token->right, fdin, fdout, shell));
	return (0);
}

int	or_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!stage_two_function(token->left, fdin, fdout, shell))
		return (stage_one_function(token->right, fdin, fdout, shell));
	return (0);
}

int	pipe_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	int	end[2];

	if (pipe(end) < 0)
		perror("pipe");
	exec_function(token, fdin, end[1], shell);
	close(end[1]);
	return (end[0]);
}
