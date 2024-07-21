/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:12:42 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/07/21 20:29:15 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_handle_or(char *str, int start, int end, t_token **token)
{
	if (!ft_add_token(OR, token))
		return (EXIT_FAILURE);
	if (ft_stage_pipe(str, start, &(*token)->left))
	{
		if (!(*token)->left)
			return (ft_throw_syntax_error("||"));
		return (PARSING_FAILURE);
	}
	if (ft_stage_or(&str[start + 2], end - (start + 2), &(*token)->right))
	{
		if (!(*token)->right)
			return (ft_throw_syntax_error("newline"));
		return (PARSING_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_stage_or(char *str, int end, t_token **token)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (!ft_strncmp(&str[i], "\"", 1))
			i += ft_index(&str[i + 1], "\"") + 1;
		else if (!ft_strncmp(&str[i], "\'", 1))
			i += ft_index(&str[i + 1], "\'") + 1;
		else if (!ft_strncmp(&str[i], "(", 1))
			i += ft_skip_parentheses(&str[i]);
		else if (!ft_strncmp(&str[i], ")", 1))
			return (ft_throw_syntax_error(")"));
		else if (!ft_strncmp(&str[i], "||", 2))
			return (ft_handle_or(str, i, end, token));
		if (!str[i])
			return (PARSING_FAILURE);
		i++;
	}
	return (ft_stage_pipe(str, end, token));
}

int	ft_handle_and(char *str, int end, t_token **token)
{
	if (!ft_add_token(AND, token))
		return (EXIT_FAILURE);
	if (ft_stage_or(str, end, &(*token)->left))
	{
		if (!(*token)->left)
			return (ft_throw_syntax_error("&&"));
		return (PARSING_FAILURE);
	}
	if (ft_stage_and(&str[end + 2], &(*token)->right))
	{
		if (!(*token)->right)
			return (ft_throw_syntax_error("newline"));
		return (PARSING_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_stage_and(char *str, t_token **token)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "\"", 1))
			i += ft_index(&str[i + 1], "\"") + 1;
		else if (!ft_strncmp(&str[i], "\'", 1))
			i += ft_index(&str[i + 1], "\'") + 1;
		else if (!ft_strncmp(&str[i], "(", 1))
			i += ft_skip_parentheses(&str[i]);
		else if (!ft_strncmp(&str[i], ")", 1))
			return (ft_throw_syntax_error(")"));
		else if (!ft_strncmp(&str[i], "&&", 2))
			return (ft_handle_and(str, i, token));
		if (!str[i])
			return (PARSING_FAILURE);
		i++;
	}
	return (ft_stage_or(str, i, token));
}
