/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_priority.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:24:32 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/07 19:59:41 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_priority_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	int	status;

	if (!token)
		return (EXIT_FAILURE);
	if (token->type == AND)
		status = ft_and_function(token, fdin, fdout, shell);
	else if (token->type == OR)
		status = ft_or_function(token, fdin, fdout, shell);
	else if (token->type == PIPE)
		status = ft_pipe_token(token, fdin, fdout, shell);
	else
		status = ft_redir_token(token, fdin, fdout, shell);
	while (wait(&shell->exit_code) > 0)
		;
	if (status)
		shell->exit_code = status;
	else if (WIFEXITED(shell->exit_code))
		shell->exit_code = WEXITSTATUS(shell->exit_code);
	if (shell->exit_code == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
	return (shell->exit_code);
}

int	ft_ambiguous_redirect(t_token *token, t_shell *shell)
{
	char	*file;

	if (token->type == REDIR_HEREDOC)
		return (EXIT_SUCCESS);
	file = ft_strdup(token->args[0]);
	if (ft_expand(token, shell))
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

int	ft_redir_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token || fdin < 0 || fdout < 0)
		return (EXIT_FAILURE);
	if (token->type >= REDIR_HEREDOC && token->type <= REDIR_IN)
	{
		if (ft_ambiguous_redirect(token->left, shell))
			return (EXIT_FAILURE);
		if (token->type == REDIR_IN)
			fdin = ft_redir_in_function(token->left);
		else if (token->type == REDIR_HEREDOC)
			fdin = ft_redir_heredoc_function(token->left);
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
		status = !((ft_redir_token(token->left, fdin, end[1], shell) == 0 \
			&& !close(end[1])) \
			&& (ft_pipe_token(token->right, end[0], fdout, shell) == 0 \
			&& !close(end[0])));
		return (status);
	}
	return (ft_redir_token(token, fdin, fdout, shell));
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
