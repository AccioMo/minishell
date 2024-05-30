/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:20:34 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/30 18:32:10 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_handle_append(char *str, int start, int end, t_token **token)
{
	char	*wd;
	int		len;

	len = ft_word_len(&str[start + 2]);
	ft_add_token(REDIR_APPEND, ">>", token);
	wd = ft_merge(str, start, &str[len + 2], end - (len + 2));
	if (ft_stage_four(&str[start + 2], len, &(*token)->left) && !(*token)->left)
		return (ft_throw_error("syntax error near unexpected token", ">>"));
	if (ft_stage_three(wd, ft_strlen(wd), &(*token)->right) && (*token)->right)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_handle_heredoc(char *str, int start, int end, t_token **token)
{
	char	*wd;
	int		len;

	len = ft_word_len(&str[start + 2]);
	ft_add_token(REDIR_HEREDOC, "<<", token);
	wd = ft_merge(str, start, &str[len + 2], end - (len + 2));
	if (ft_stage_four(&str[start + 2], len, &(*token)->left) && !(*token)->left)
		return (ft_throw_error("syntax error near unexpected token", "<<"));
	if (ft_stage_three(wd, ft_strlen(wd), &(*token)->right) && (*token)->right)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_handle_redir_in(char *str, int start, int end, t_token **token)
{
	char	*wd;
	int		len;

	ft_add_token(REDIR_IN, "<", token);
	len = ft_word_len(&str[start + 1]);
	wd = ft_merge(str, start, &str[len + 1], end - (len + 1));
	if (ft_stage_four(&str[start + 1], len, &(*token)->left) && !(*token)->left)
		return (ft_throw_error("syntax error near unexpected token", "<"));
	if (ft_stage_three(wd, ft_strlen(wd), &(*token)->right) && (*token)->right)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_handle_redir_out(char *str, int start, int end, t_token **token)
{
	char	*wd;
	int		len;

	len = ft_word_len(&str[start + 1]);
	ft_add_token(REDIR_OUT, ">", token);
	wd = ft_merge(str, start, &str[len + 1], end - (len + 1));
	if (ft_stage_four(&str[start + 1], len, &(*token)->left) && !(*token)->left)
		return (ft_throw_error("syntax error near unexpected token", ">"));
	if (ft_stage_three(wd, ft_strlen(wd), &(*token)->right) && (*token)->right)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_stage_three(char *str, int end, t_token **token)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (!ft_strncmp(&str[i], "\"", 1))
			i += ft_index(&str[i + 1], '\"') + 1;
		else if (!ft_strncmp(&str[i], "(", 1))
			i += ft_skip_parentheses(&str[i]);
		else if (!ft_strncmp(&str[i], ">>", 2))
			return (ft_handle_append(str, i, end, token));
		else if (!ft_strncmp(&str[i], "<<", 2))
			return (ft_handle_heredoc(str, i, end, token));
		else if (!ft_strncmp(&str[i], "<", 1))
			return (ft_handle_redir_in(str, i, end, token));
		else if (!ft_strncmp(&str[i], ">", 1))
			return (ft_handle_redir_out(str, i, end, token));
		i++;
	}
	return (ft_stage_four(str, end, token));
}
