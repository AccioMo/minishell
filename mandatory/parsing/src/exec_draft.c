/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_draft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:24:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/11 19:33:08 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int stage_one_function(t_token *token, t_shell *env)
{
	if (token->type == AND)
		return (and_function(token, env));
	else if (token->type == OR)
		return (or_function(token, env));
	return (stage_two_function(token, env));
}

int	stage_two_function(t_token *token, t_shell *env)
{
	if (token->type == PIPE)
		pipe_function(token, env);
	else if (token->type == WORD)
		exec_function(token, env);
	else if (token->type == REDIR_IN)
		redir_function(token, env);
	else if (token->type == REDIR_OUT)
		redir_function(token, env);
	// else if (token->type == SUBSHELL)
	// 	recursive_function(token->left, env);
}

int	and_function(t_token *token, t_shell *env)
{
	if (recursive_function(token->left))
		recursive_function(token->right);
	else
		return (0);
}

int	or_function(t_token *token, t_shell *env)
{
	if (!recursive_function(token->left))
		recursive_function(token->right);
	else
		return (0);
}

int	pipe_function(t_token *token, int fdin, int fdout, t_shell *env)
{
	int	fd;

	fd = exec_function(token->left, fdin, fdout);
	if (token->right->type == PIPE)
		pipe_function(token->right, fd, -1, env);
	else if (token->right->type == WORD)
		exec_function(token->left, fd, 1);
	// else if (token->right->type == SUBSHELL)
	// 	recursive_function(token->left, env);
}
