/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:12:42 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/21 18:17:49 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_skip_parentheses(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '(')
		i++;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "\"", 1))
			i += ft_index(&str[i + 1], '\"') + 1;
		else if (!ft_strncmp(&str[i], "\'", 1))
			i += ft_index(&str[i + 1], '\'') + 1;
		else if (!ft_strncmp(&str[i], "(", 1))
			i += ft_skip_parentheses(&str[i]);
		else if (!ft_strncmp(&str[i], ")", 1))
			return (i);
		else
			i++;
	}
	return (i);
}

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

void	ft_parse_word(char *str, int end, t_token **token)
{
	char	*word;

	word = ft_substr(str, 0, end);
	ft_add_token(WORD, NULL, token);
	(*token)->args = ft_cmd_split(word);
}

int	ft_throw_error(char *msg, char *word)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" `", 2);
	ft_putstr_fd(word, 2);
	ft_putstr_fd("`.\n", 2);
	return (EXIT_FAILURE);
}

int	ft_stage_four(char *str, int end, t_token **token)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && i < end)
	{
		if (ft_whitespace(str[i]))
			i++;
		else if (!ft_strncmp(&str[i], "(", 1))
		{
			word = ft_substr(&str[i + 1], 0, ft_skip_parentheses(&str[i + 1]));
			ft_add_token(SUBSHELL, NULL, token);
			ft_stage_one(word, &(*token)->right);
			return (EXIT_SUCCESS);
		}
		else
		{
			word = ft_substr(&str[i], 0, end - i);
			ft_parse_word(word, end, token);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

int	ft_stage_three(char *str, int end, t_token **token)
{
	char	*word;
	int		i;
	int		j;

	i = 0;
	while (i < end)
	{
		if (!ft_strncmp(&str[i], "\"", 1))
			i += ft_index(&str[i + 1], '\"') + 1;
		else if (!ft_strncmp(&str[i], "(", 1))
			i += ft_skip_parentheses(&str[i]);
		else if (!ft_strncmp(&str[i], ">>", 2))
		{
			ft_add_token(REDIR_APPEND, ">>", token);
			j = i + 2 + ft_word_len(&str[i + 2]);
			word = ft_merge(str, i, &str[j], end - j);
			if (ft_stage_four(&str[i + 2], ft_word_len(&str[i + 2]), &(*token)->left) && !(*token)->left)
				return (ft_throw_error("syntax error near unexpected token", ">>"));
			if (ft_stage_three(word, ft_strlen(word), &(*token)->right) && (*token)->right)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		else if (!ft_strncmp(&str[i], "<<", 2))
		{
			ft_add_token(REDIR_HEREDOC, "<<", token);
			j = i + 2 + ft_word_len(&str[i + 2]);
			word = ft_merge(str, i, &str[j], end - j);
			if (ft_stage_four(&str[i + 2], ft_word_len(&str[i + 2]), &(*token)->left) && !(*token)->left)
				return (ft_throw_error("syntax error near unexpected token", "<<"));
			if (ft_stage_three(word, ft_strlen(word), &(*token)->right) && (*token)->right)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		else if (!ft_strncmp(&str[i], "<", 1))
		{
			ft_add_token(REDIR_IN, "<", token);
			j = i + 1 + ft_word_len(&str[i + 1]);
			word = ft_merge(str, i, &str[j], end - j);
			if (ft_stage_four(&str[i + 1], ft_word_len(&str[i + 1]), &(*token)->left) && !(*token)->left)
				return (ft_throw_error("syntax error near unexpected token", "<"));
			if (ft_stage_three(word, ft_strlen(word), &(*token)->right) && (*token)->right)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		else if (!ft_strncmp(&str[i], ">", 1))
		{
			ft_add_token(REDIR_OUT, ">", token);
			j = i + 1 + ft_word_len(&str[i + 1]);
			word = ft_merge(str, i, &str[j], end - j);
			if (ft_stage_four(&str[i + 1], ft_word_len(&str[i + 1]), &(*token)->left) && !(*token)->left)
				return (ft_throw_error("syntax error near unexpected token", ">"));
			if (ft_stage_three(word, ft_strlen(word), &(*token)->right) && (*token)->right)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (ft_stage_four(str, end, token));
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
		{
			ft_add_token(PIPE, "|", token);
			if (ft_stage_three(str, i, &(*token)->left))
			{
				if (!(*token)->left)
					ft_throw_error("syntax error near unexpected token", "|");
				return (EXIT_FAILURE);
			}
			if (ft_stage_two(&str[i + 1], end - (i + 1), &(*token)->right))
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
		i++;
	}
	return (ft_stage_three(str, end, token));
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
		{
			ft_add_token(AND, "&&", token);
			if (ft_stage_two(str, i, &(*token)->left))
			{
				if (!(*token)->left)
					ft_throw_error("syntax error near unexpected token", "&&");
				return (EXIT_FAILURE);
			}
			if (ft_stage_one(&str[i + 2], &(*token)->right))
			{
				if (!(*token)->right)
					ft_throw_error("syntax error near unexpected token", "newline");
				return (EXIT_FAILURE);
			}
			return (EXIT_SUCCESS);
		}
		else if (!ft_strncmp(&str[i], "||", 2))
		{
			ft_add_token(OR, "||", token);
			if (ft_stage_two(str, i, &(*token)->left))
			{
				if (!(*token)->left)
					ft_throw_error("syntax error near unexpected token", "||");
				return (EXIT_FAILURE);
			}
			if (ft_stage_one(&str[i + 2], &(*token)->right))
			{
				if (!(*token)->right)
					ft_throw_error("syntax error near unexpected token", "newline");
				return (EXIT_FAILURE);
			}
			return (EXIT_SUCCESS);
		}
		else
			i++;
	}
	return (ft_stage_two(str, i, token));
}
