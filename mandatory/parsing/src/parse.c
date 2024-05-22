/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:29:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/22 19:41:01 by zouddach         ###   ########.fr       */
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
	if (!token)
		return ;
	if (token->left)
		ft_free_tree(token->left);
	if (token->right)
		ft_free_tree(token->right);
	ft_free(token->args);
	free(token);
}

int	ft_open_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			while (line[++i] && line[i] != '\'')
				;
			if (!line[i])
				return (1);
		}
		else if (line[i] == '\"')
		{
			while (line[++i] && line[i] != '\"')
				;
			if (!line[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_open_parentheses(char *line)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			i += ft_index(&line[i + 1], '\"') + 1;
		else if (line[i] == '\'')
			i += ft_index(&line[i + 1], '\'') + 1;
		else if (line[i] == '(')
			p++;
		else if (line[i] == ')')
			p--;
		i++;
	}
	return (p);
}

int	ft_parse(char *line, t_shell *shell)
{
	int		i;

	i = 0;
	if (ft_open_quotes(line))
	{
		ft_throw_error("syntax error: open quotes", line);
		return (EXIT_FAILURE);
	}
	if (ft_open_parentheses(line))
	{
		ft_throw_error("syntax error: open parentheses", line);
		return (EXIT_FAILURE);
	}
	if (ft_stage_one(line, &shell->root))
	{
		// ft_free_tree(shell->root);
		shell->root = NULL;
		return (EXIT_FAILURE);
	}
	// if (ft_late_work(shell->root, shell)) //Moved to execution
	// {
	// 	// ft_free_tree(shell->root);
	// 	shell->root = NULL;
	// 	return (EXIT_FAILURE);
	// }
	return (EXIT_SUCCESS);
}
