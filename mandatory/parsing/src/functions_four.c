/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_four.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:36:21 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/07/09 23:43:45 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_throw_syntax_error(char *word)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(word, 2);
	ft_putstr_fd("`.\n", 2);
	return (PARSING_FAILURE);
}

int	valid_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_whitespace(line[i]))
			return (1);
		i++;
	}
	free(line);
	return (0);
}

int	ft_handle_pipe(char *str, int start, int end, t_token **token)
{
	if (!ft_add_token(PIPE, token))
		return (EXIT_FAILURE);
	if (ft_stage_redir(str, start, &(*token)->left))
	{
		if (!(*token)->left)
			return (ft_throw_syntax_error("|"));
		return (PARSING_FAILURE);
	}
	if (ft_stage_pipe(&str[start + 1], end - (start + 1), &(*token)->right))
	{
		if (!(*token)->right)
		{
			ft_throw_syntax_error("newline");
			ft_free_tree(*token);
			*token = NULL;
		}
		return (PARSING_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_stage_pipe(char *str, int end, t_token **token)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (!ft_strncmp(&str[i], "\"", 1))
			i += ft_index(&str[i + 1], '\"') + 1;
		else if (!ft_strncmp(&str[i], "\'", 1))
			i += ft_index(&str[i + 1], '\'') + 1;
		else if (!ft_strncmp(&str[i], "(", 1))
			i += ft_skip_parentheses(&str[i]);
		else if (!ft_strncmp(&str[i], "|", 1))
			return (ft_handle_pipe(str, i, end, token));
		i++;
	}
	return (ft_stage_redir(str, end, token));
}
