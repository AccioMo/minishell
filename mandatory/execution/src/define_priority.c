/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_priority.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:24:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/22 04:22:23 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	ft_ambiguous_redirect(t_token *token, t_shell *shell)
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

int	ft_redir_token(t_token *token, int fdin[2], int fdout, t_shell *shell)
{
	if (!token || fdin[0] < 0 || fdout < 0)
		return (EXIT_FAILURE);
	if (token->type >= REDIR_HEREDOC && token->type <= REDIR_IN)
	{
		if (token->type != REDIR_HEREDOC && \
			ft_ambiguous_redirect(token->left, shell))
			return (EXIT_FAILURE);
		if (token->type == REDIR_HEREDOC || token->type == REDIR_IN)
			return (ft_handle_redirs_in(token, fdin, fdout, shell));
		else
			return (ft_handle_redirs_out(token, fdin, fdout, shell));
	}
	return (ft_execution_token(token, fdin, fdout, shell));
}

int	ft_pipe_token(t_token *token, int fdin, int fdout, t_shell *sh)
{
	int	st;
	int	end[2];

	if (!token)
		return (EXIT_FAILURE);
	if (token->type == PIPE)
	{
		if (pipe(end) < 0)
			perror("pipe");
		st = ft_redir_token(token->left, (int [2]){fdin, end[0]}, end[1], sh);
		if (fdin != 0)
			close(fdin);
		close(end[1]);
		if (st == 2)
		{
			close(end[0]);
			return (EXIT_FAILURE);
		}
		st = ft_pipe_token(token->right, end[0], fdout, sh);
		close(end[0]);
		return (st);
	}
	return (ft_redir_token(token, (int [2]){fdin, -1}, fdout, sh));
}

int	ft_execution_token(t_token *token, int fdin[2], int fdout, t_shell *shell)
{
	int	exit_status;

	if (!token)
	{
		if (!shell->subshell)
			ft_close_fds(fdin[0], fdout);
		return (EXIT_FAILURE);
	}
	exit_status = 0;
	if (token->type == WORD)
		exit_status = ft_exec_function(token, fdin, fdout, shell);
	else if (token->type == SUBSHELL)
	{
		shell->subshell++;
		exit_status = ft_first_token(token->right, fdin[0], fdout, shell);
		shell->subshell--;
	}
	if (!shell->subshell)
		ft_close_fds(fdin[0], fdout);
	return (exit_status);
}
