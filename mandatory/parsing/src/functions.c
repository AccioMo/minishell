/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:12:42 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/10 19:47:28 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*ft_add_token(t_type type, char *str, t_token **token)
{
	t_token	*new;

	if (*token)
		return (*token);
	new = (t_token *)malloc(sizeof(t_token));
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	new->args = NULL;
	if (str)
	{
		new->args = (char **)malloc(sizeof(char *) * 2);
		new->args[0] = str;
	}
	*token = new;
	return (new);
}

void	ft_stage_four(char *str, int end, t_token **token)
{
	char	*word;
	int		i;
	int		j;

	i = 0;
	word = ft_substr(str, 0, end);
	ft_add_token(WORD, NULL, token);
	(*token)->args = ft_cmd_split(word);
}

void	ft_stage_three(char *str, int end, t_token **token)
{
	t_io	*io;
	char	*word;
	int		i;
	int		j;

	i = 0;
	io = (t_io *)malloc(sizeof(t_io));
	while (i < end)
	{
		if (!ft_strncmp(&str[i], "(", 1))
			i += ft_rindex(&str[i], ')');
		else if (!ft_strncmp(&str[i], ">>", 2))
		{
			ft_add_token(REDIR_APPEND, ">>", token);
			j = i + 2 + ft_word_len(&str[i + 2]);
			word = ft_merge(str, i, &str[j], end - j);
			ft_stage_three(word, ft_strlen(word), &(*token)->right);
			// word = ft_first_word(&str[i + 2]);
			ft_stage_four(&str[i + 2], ft_word_len(word), &(*token)->left);
			return ;
		}
		else if (!ft_strncmp(&str[i], "<<", 2))
		{
			ft_add_token(REDIR_HEREDOC, "<<", token);
			j = i + 2 + ft_word_len(&str[i + 2]);
			word = ft_merge(str, i, &str[j], end - j);
			ft_stage_three(word, ft_strlen(word), &(*token)->right);
			// word = ft_first_word(&str[i + 2]);
			ft_stage_four(&str[i + 2], ft_word_len(word), &(*token)->left);
			return ;
		}
		else if (!ft_strncmp(&str[i], "<", 1))
		{
			ft_add_token(REDIR_IN, "<", token);
			j = i + 1 + ft_word_len(&str[i + 1]);
			word = ft_merge(str, i, &str[j], end - j);
			ft_stage_three(word, ft_strlen(word), &(*token)->right);
			// word = ft_first_word(&str[i + 1]);
			ft_stage_four(&str[i + 1], ft_word_len(word), &(*token)->left);
			return ;
		}
		else if (!ft_strncmp(&str[i], ">", 1))
		{
			ft_add_token(REDIR_OUT, ">", token);
			j = i + 1 + ft_word_len(&str[i + 1]);
			word = ft_merge(str, i, &str[j], end - j);
			ft_stage_three(word, ft_strlen(word), &(*token)->right);
			// word = ft_first_word(&str[i + 1]);
			ft_stage_four(&str[i + 1], ft_word_len(word), &(*token)->left);
			return ;
		}
		i++;
	}
	ft_stage_four(str, end, token);
}

void	ft_stage_two(char *str, int end, t_token **token)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (!ft_strncmp(&str[i], "(", 1))
			i += ft_rindex(&str[i], ')');
		else if (!ft_strncmp(&str[i], "|", 1))
		{
			ft_add_token(PIPE, "|", token);
			ft_stage_two(&str[i + 1], end - (i + 1), &(*token)->right);
			ft_stage_three(str, i, &(*token)->left);
			return ;
		}
		i++;
	}
	ft_stage_three(str, end, token);
}

void	ft_stage_one(char *str, t_token **token)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "(", 1))
			i += ft_rindex(&str[i], ')');
		else if (!ft_strncmp(&str[i], ")", 1))
			return ;
		else if (!ft_strncmp(&str[i], "&&", 2))
		{
			ft_add_token(AND, "&&", token);
			ft_stage_one(&str[i + 2], &(*token)->right);
			ft_stage_two(str, i, &(*token)->left);
			return ;
		}
		else if (!ft_strncmp(&str[i], "||", 2))
		{
			ft_add_token(OR, "||", token);
			ft_stage_one(&str[i + 2], &(*token)->right);
			ft_stage_two(str, i, &(*token)->left);
			return ;
		}
		i++;
	}
	ft_stage_two(str, i, token);
}
