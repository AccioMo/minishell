/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:20:34 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/02 18:04:00 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_handle_append(char *str, int start, int end, t_token **token)
{
	char	*wd;
	int		len;

	len = ft_word_len(&str[start]);
	if (!ft_add_token(REDIR_APPEND, ">>", token))
		return (EXIT_FAILURE);
	wd = ft_merge(str, start - 2, &str[start + len], end - (start + len));
	if (ft_stage_four(&str[start], len, &(*token)->left) && !(*token)->left)
		return (ft_throw_syntax_error(">>"));
	if (ft_stage_three(wd, ft_strlen(wd), &(*token)->right) && (*token)->right)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_handle_heredoc(char *str, int start, int end, t_token **token)
{
	char	*wd;
	int		len;

	len = ft_word_len(&str[start]);
	if (!ft_add_token(REDIR_HEREDOC, "<<", token))
		return (EXIT_FAILURE);
	wd = ft_merge(str, start - 2, &str[start + len], end - (start + len));
	if (ft_stage_four(&str[start], len, &(*token)->left) && !(*token)->left)
		return (ft_throw_syntax_error("<<"));
	if (ft_stage_three(wd, ft_strlen(wd), &(*token)->right) && (*token)->right)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_handle_redir_in(char *str, int start, int end, t_token **token)
{
	char	*wd;
	int		len;

	len = ft_word_len(&str[start]);
	if (!ft_add_token(REDIR_IN, "<", token))
		return (EXIT_FAILURE);
	wd = ft_merge(str, start - 1, &str[start + len], end - (start + len));
	if (ft_stage_four(&str[start], len, &(*token)->left) && !(*token)->left)
		return (ft_throw_syntax_error("<"));
	if (ft_stage_three(wd, ft_strlen(wd), &(*token)->right) && (*token)->right)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_handle_redir_out(char *str, int start, int end, t_token **token)
{
	char	*wd;
	int		len;

	len = ft_word_len(&str[start]);
	if (!ft_add_token(REDIR_OUT, ">", token))
		return (EXIT_FAILURE);
	wd = ft_merge(str, start - 1, &str[start + len], end - (start + len));
	if (ft_stage_four(&str[start], len, &(*token)->left) && !(*token)->left)
		return (ft_throw_syntax_error(">"));
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
			return (ft_handle_append(str, i + 2, end, token));
		else if (!ft_strncmp(&str[i], "<<", 2))
			return (ft_handle_heredoc(str, i + 2, end, token));
		else if (!ft_strncmp(&str[i], "<", 1))
			return (ft_handle_redir_in(str, i + 1, end, token));
		else if (!ft_strncmp(&str[i], ">", 1))
			return (ft_handle_redir_out(str, i + 1, end, token));
		i++;
	}
	return (ft_stage_four(str, end, token));
}
