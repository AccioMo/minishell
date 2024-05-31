/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:12:42 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/31 20:06:07 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_handle_pipe(char *str, int start, int end, t_token **token)
{
	ft_add_token(PIPE, "|", token);
	if (ft_stage_three(str, start, &(*token)->left))
	{
		if (!(*token)->left)
			ft_throw_error("syntax error near unexpected token", "|");
		return (EXIT_FAILURE);
	}
	if (ft_stage_two(&str[start + 1], end - (start - 1), &(*token)->right))
	{
		if (!(*token)->right)
		{
			ft_free_tree(*token);
			*token = NULL;
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_stage_two(char *str, int end, t_token **token)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (!ft_strncmp(&str[i], "\"", 1))
			i += ft_index(&str[i + 1], '\"') + 1;
		else if (!ft_strncmp(&str[i], "(", 1))
			i += ft_skip_parentheses(&str[i]);
		else if (!ft_strncmp(&str[i], "|", 1))
			return (ft_handle_pipe(str, i, end, token));
		i++;
	}
	return (ft_stage_three(str, end, token));
}

int	ft_handle_and(char *str, int end, t_token **token)
{
	ft_add_token(AND, "&&", token);
	if (ft_stage_two(str, end, &(*token)->left))
	{
		if (!(*token)->left)
			ft_throw_error("syntax error near unexpected token", "&&");
		return (EXIT_FAILURE);
	}
	if (ft_stage_one(&str[end + 2], &(*token)->right))
	{
		if (!(*token)->right)
			ft_throw_error("syntax error near unexpected token", "newline");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_handle_or(char *str, int end, t_token **token)
{
	ft_add_token(OR, "||", token);
	if (ft_stage_two(str, end, &(*token)->left))
	{
		if (!(*token)->left)
			ft_throw_error("syntax error near unexpected token", "||");
		return (EXIT_FAILURE);
	}
	if (ft_stage_one(&str[end + 2], &(*token)->right))
	{
		if (!(*token)->right)
			ft_throw_error("syntax error near unexpected token", "newline");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_stage_one(char *str, t_token **token)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "\"", 1))
			i += ft_index(&str[i + 1], '\"') + 1;
		else if (!ft_strncmp(&str[i], "(", 1))
			i += ft_skip_parentheses(&str[i]);
		else if (!ft_strncmp(&str[i], "&&", 2))
			return (ft_handle_and(str, i, token));
		else if (!ft_strncmp(&str[i], "||", 2))
			return (ft_handle_or(str, i, token));
		i++;
	}
	return (ft_stage_two(str, i, token));
}
