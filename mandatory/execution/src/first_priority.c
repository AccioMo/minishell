/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_priority.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:16:19 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/25 21:15:16 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_or_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (shell->root == token)
		shell->exit_code = ft_priority_token(token->left, fdin, fdout, shell);
	if (shell->exit_code == SIGINT || shell->exit_code == SIGQUIT)
		return (shell->exit_code);
	if (shell->exit_code)
	{
		if (!(token->right->type == OR || token->right->type == AND))
			return (ft_pipe_token(token->right, fdin, fdout, shell));
		ft_priority_token(token->right->left, fdin, fdout, shell);
	}
	if (token->right->type == OR || token->right->type == AND)
		return (ft_priority_token(token->right, fdin, fdout, shell));
	return (shell->exit_code);
}

int	ft_and_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (shell->root == token)
		shell->exit_code = ft_priority_token(token->left, fdin, fdout, shell);
	if (shell->exit_code == SIGINT || shell->exit_code == SIGQUIT)
		return (shell->exit_code);
	if (!shell->exit_code)
	{
		if (!(token->right->type == OR || token->right->type == AND))
			return (ft_pipe_token(token->right, fdin, fdout, shell));
		ft_priority_token(token->right->left, fdin, fdout, shell);
	}
	if (token->right->type == OR || token->right->type == AND)
		return (ft_priority_token(token->right, fdin, fdout, shell));
	return (shell->exit_code);
}

int	ft_first_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == AND)
		return (ft_and_function(token, fdin, fdout, shell));
	else if (token->type == OR)
		return (ft_or_function(token, fdin, fdout, shell));
	return (ft_pipe_token(token, fdin, fdout, shell));
}

int	ft_priority_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	int	status;
	int	exit_code;

	if (!token)
		return (EXIT_FAILURE);
	status = ft_first_token(token, fdin, fdout, shell);
	if (waitpid(shell->last_pid, &exit_code, 0) > 0)
		ft_reset_term();
	else
		exit_code = status;
	while (wait(NULL) > 0)
		ft_reset_term();
	if (exit_code == SIGINT)
		ft_putchar_fd('\n', 1);
	else if (exit_code == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
	signal(SIGQUIT, main_sig_handler);
	signal(SIGINT, main_sig_handler);
	if (WIFEXITED(exit_code))
		shell->exit_code = WEXITSTATUS(exit_code);
	else if (WIFSIGNALED(exit_code))
		shell->exit_code = WTERMSIG(exit_code) + 128;
	else
		shell->exit_code = status;
	return (set_exit_code(shell->exit_code, true));
}
