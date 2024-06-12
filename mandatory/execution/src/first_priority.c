/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_priority.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:16:19 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/12 18:04:00 by mzeggaf          ###   ########.fr       */
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
		status = ft_redir_token(token, fdin, fdout, shell);
	return (status);
}

int	ft_priority_token(t_token *token, int fdin, int fdout, t_shell *shell)
{
	int		exit_code;
	int		status;

	if (!token)
		return (EXIT_FAILURE);
	status = ft_first_token(token, fdin, fdout, shell);
	waitpid(shell->last_pid, &shell->exit_code, 0);
	while (wait(&exit_code) > 0)
		;
	if (status)
		shell->exit_code = status;
	else if (WIFEXITED(shell->exit_code))
		shell->exit_code = WEXITSTATUS(shell->exit_code);
	if (shell->exit_code == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
	shell->exit_code = set_exit_code(shell->exit_code, true);
	return (shell->exit_code);
}
