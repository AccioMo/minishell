/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:29:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/15 20:18:36 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_print_tree(t_token *token)
{
	int	i;

	while (token)
	{
		if (token->type == WORD)
		{
			printf("WORD\n");
			i = 0;
			while (token->args[i])
				printf("args: %s\n", token->args[i++]);
		}
		else if (token->type == PIPE)
			printf("PIPE\n");
		else if (token->type == AND)
			printf("AND\n");
		else if (token->type == OR)
			printf("OR\n");
		else if (token->type == REDIR_IN)
			printf("REDIR_IN\n");
		else if (token->type == REDIR_OUT)
			printf("REDIR_OUT\n");
		else if (token->type == REDIR_APPEND)
			printf("REDIR_APPEND\n");
		else if (token->type == REDIR_HEREDOC)
			printf("REDIR_HEREDOC\n");
		else if (token->type == SUBSHELL)
			printf("SUBSHELL\n");
		if (token->left)
			ft_print_tree(token->left);
		token = token->right;
	}
}

void	ft_free_tree(t_token *token)
{
	if (token->left)
		ft_free_tree(token->left);
	if (token->right)
		ft_free_tree(token->right);
	free(token);
}

int	ft_parse(char *line, t_shell *shell)
{
	int		i;

	i = 0;
	shell->root = NULL;
	if (ft_stage_one(line, &shell->root))
	{
		ft_free_tree(shell->root);
		shell->root = NULL;
		return (EXIT_FAILURE);
	}
}
