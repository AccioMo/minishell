/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_draft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:24:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/12 18:14:35 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	stage_one_function(t_token *token, t_shell *shell)
{
	if (token->type == AND)
		return (and_function(token, shell));
	else if (token->type == OR)
		return (or_function(token, shell));
	return (stage_two_function(token, shell));
}

int	stage_two_function(t_token *token, t_shell *shell)
{
	if (token->type == PIPE)
		pipe_function(token, 0, 1, shell);
	else if (token->type == WORD)
		exec_function(token, 0, 1, shell);
	return (1);
	// else if (token->type == REDIR_IN)
	// 	redir_function(token, shell);
	// else if (token->type == REDIR_OUT)
	// 	redir_function(token, shell);
	// else if (token->type == SUBSHELL)
	// 	recursive_function(token->left, shell);
}

int	and_function(t_token *token, t_shell *shell)
{
	if (stage_two_function(token->left, shell))
		stage_one_function(token->right, shell);
	else
		return (0);
}

int	or_function(t_token *token, t_shell *shell)
{
	if (!stage_two_function(token->left, shell))
		stage_one_function(token->right, shell);
	else
		return (0);
}

int	pipe_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	int	end[2];

	if (pipe(end) < 0)
		perror("pipe");
	exec_function(token->left, fdin, end[1], shell);
	// close(end[1]);
	if (token->right->type == PIPE)
		pipe_function(token->right, end[0], fdout, shell);
	else if (token->right->type == WORD)
		exec_function(token->right, end[0], fdout, shell);
	close(end[0]);
}
