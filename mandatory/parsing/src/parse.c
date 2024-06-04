/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:29:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/04 05:39:59 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		ft_throw_syntax_error(line);
		return (EXIT_FAILURE);
	}
	if (ft_open_parentheses(line))
	{
		ft_throw_syntax_error(line);
		return (EXIT_FAILURE);
	}
	if (ft_stage_one(line, &shell->root))
	{
		ft_free_tree(shell->root);
		shell->root = NULL;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
