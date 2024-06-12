/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_priority.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:24:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/12 19:46:26 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_ambiguous_redirect(t_token *token, t_shell *shell)
{
	char	*file;

	if (!token)
		return (EXIT_FAILURE);
	file = ft_strdup(token->args[0]);
	if (ft_expand_variables(token, shell) || ft_expand_wildcard(token))
	{
		free(file);
		return (EXIT_FAILURE);
	}
	if (ft_array_len(token->args) != 1 || !ft_strlen(token->args[0]))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		free(file);
		return (EXIT_FAILURE);
	}
	free(file);
	return (EXIT_SUCCESS);
}

int	ft_next_heredoc(t_shell *shell)
{
	int	fd;

	if (!shell->heredocs)
		return (-1);
	fd = shell->heredocs->fd;
	shell->heredocs = shell->heredocs->next;
	return (fd);
}

int	ft_redir_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token || fdin < 0 || fdout < 0)
		return (EXIT_FAILURE);
	if (token->type >= REDIR_HEREDOC && token->type <= REDIR_IN)
	{
		if (token->type != REDIR_HEREDOC && \
			ft_ambiguous_redirect(token->left, shell))
			return (EXIT_FAILURE);
		if (token->type == REDIR_IN)
			fdin = ft_redir_in_function(token->left);
		else if (token->type == REDIR_HEREDOC)
			fdin = ft_next_heredoc(shell);
		else if (token->type == REDIR_OUT)
			fdout = ft_redir_out_function(token->left);
		else if (token->type == REDIR_APPEND)
			fdout = ft_redir_append_function(token->left);
		if (!token->right)
			return (EXIT_SUCCESS);
		return (ft_redir_token(token->right, fdin, fdout, shell));
	}
	return (ft_execution_token(token, fdin, fdout, shell));
}

int	ft_pipe_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	int	status;
	int	end[2];

	if (!token)
		return (EXIT_FAILURE);
	if (token->type == PIPE)
	{
		if (pipe(end) < 0)
			perror("pipe");
		ft_redir_token(token->left, fdin, end[1], shell);
		if (fdin != 0)
			close(fdin);
		close(end[1]);
		status = ft_pipe_token(token->right, end[0], fdout, shell);
		close(end[0]);
		return (status);
	}
	return (ft_redir_token(token, fdin, fdout, shell));
}

int	ft_execution_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	int	exit_status;

	if (!token)
	{
		if (!shell->subshell)
			ft_close_fds(fdin, fdout);
		return (EXIT_FAILURE);
	}
	exit_status = 0;
	if (token->type == WORD)
		exit_status = ft_exec_function(token, fdin, fdout, shell);
	else if (token->type == SUBSHELL)
	{
		shell->subshell = 1;
		exit_status = ft_first_token(token->right, fdin, fdout, shell);
		shell->subshell = 0;
	}
	if (!shell->subshell)
		ft_close_fds(fdin, fdout);
	return (exit_status);
}
