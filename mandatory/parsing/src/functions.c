/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:12:42 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/10 00:22:23 by mzeggaf          ###   ########.fr       */
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
	new->args = (char **)malloc(sizeof(char *) * 2);
	new->args[0] = str;
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
	ft_add_token(WORD, word, token);
	// while (str[i] && i < end)
	// {
		// if (!ft_strncmp(&str[i], "(", 1))
		// {
		// 	i = ft_rindex(&str[i], ')') + 1;
		// 	word = ft_substr(str, 1, i - 1);
		// 	ft_stage_one(word, token);
		// }
		// else if (!ft_strncmp(&str[i], "\"", 1))
		// 	;
		// else if (!ft_strncmp(&str[i], "\'", 1))
		// 	;
		// else if (!ft_strncmp(&str[i], " ", 1))
		// 	;
		// else
		// {
			// j = ft_word_len(&str[i]);
			// ft_add_token(WORD, &str[i], token);
			// i += j;
		// }
		// i++;
	// }
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
			io->infile = ft_first_word(&str[i + 1]);
			io->type = APPEND;
			i += ft_word_len(&str[i + 2]) + 2;
		}
		else if (!ft_strncmp(&str[i], "<<", 2))
		{
			io->infile = ft_first_word(&str[i + 1]);
			io->type = HEREDOC;
			i += ft_word_len(&str[i + 2]) + 2;
		}
		else if (!ft_strncmp(&str[i], "<", 1))
		{
			io->outfile = ft_first_word(&str[i + 1]);
			io->type = READ;
			i += ft_word_len(&str[i + 1]) + 1;
		}
		else if (!ft_strncmp(&str[i], ">", 1))
		{
			io->outfile = ft_first_word(&str[i + 1]);
			io->type = WRITE;
			i += ft_word_len(&str[i + 1]) + 1;
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
