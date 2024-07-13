/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_priority.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:16:19 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/13 19:56:30 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_or_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (ft_priority_token(token->left, fdin, fdout, shell))
		return (ft_priority_token(token->right, fdin, fdout, shell));
	return (0);
}

int	ft_and_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!ft_priority_token(token->left, fdin, fdout, shell))
		return (ft_priority_token(token->right, fdin, fdout, shell));
	return (0);
}

int	ft_first_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	int	status;

	shell->subshell = 0;
	if (!token)
		return (EXIT_FAILURE);
	if (token->type == AND)
		status = ft_and_function(token, fdin, fdout, shell);
	else if (token->type == OR)
		status = ft_or_function(token, fdin, fdout, shell);
	else if (token->type == PIPE)
	{
		shell->subshell = 1;
		status = ft_pipe_token(token, fdin, fdout, shell);
		shell->subshell = 0;
	}
	else
		status = ft_redir_token(token, (int [2]){fdin, -1}, fdout, shell);
	return (status);
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
	while (wait(NULL) > 0)
		ft_reset_term();
	if (exit_code == SIGINT)
		ft_putchar_fd('\n', 1);
	else if (exit_code == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
	shell->exit_code = exit_code;
	signal(SIGQUIT, main_sig_handler);
	signal(SIGINT, main_sig_handler);
	if (status)
		shell->exit_code = status;
	else if (WIFEXITED(shell->exit_code))
		shell->exit_code = WEXITSTATUS(shell->exit_code);
	shell->exit_code = set_exit_code(shell->exit_code, true);
	return (shell->exit_code);
}
