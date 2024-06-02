/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_functions_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:12:42 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/02 18:04:32 by zouddach         ###   ########.fr       */
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
	if (!new)
		return (NULL);
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	new->args = NULL;
	if (str)
	{
		new->args = (char **)malloc(sizeof(char *) * 2);
		if (!new->args)
			return (NULL);
		new->args[0] = str;
	}
	*token = new;
	return (new);
}

int	ft_parse_word(char *str, int end, t_token **token)
{
	char	*word;

	word = ft_substr(str, 0, end);
	if (ft_add_token(WORD, NULL, token))
		return (EXIT_FAILURE);
	(*token)->args = ft_cmd_split(word);
	if ((*token)->args == NULL)
		return (EXIT_FAILURE);
	free(word);
	free(str);
	return (EXIT_SUCCESS);
}

int	ft_throw_syntax_error(char *msg, char *word)
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
			if (ft_add_token(SUBSHELL, NULL, token))
				return (EXIT_FAILURE);
			ft_stage_one(word, &(*token)->right);
			return (EXIT_SUCCESS);
		}
		else
		{
			word = ft_substr(&str[i], 0, end - i);
			if (ft_parse_word(word, end, token))
				return (EXIT_FAILURE);
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
			if (ft_add_token(REDIR_APPEND, ">>", token))
				return (EXIT_FAILURE);
			j = i + 2 + ft_word_len(&str[i + 2]);
			word = ft_merge(str, i, &str[j], end - j);
			if (ft_stage_four(&str[i + 2], ft_word_len(&str[i + 2]), &(*token)->left) && !(*token)->left)
				return (ft_throw_syntax_error(">>"));
			if (ft_stage_three(word, ft_strlen(word), &(*token)->right) && (*token)->right)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		else if (!ft_strncmp(&str[i], "<<", 2))
		{
			if (ft_add_token(REDIR_HEREDOC, "<<", token))
				return (EXIT_FAILURE);
			j = i + 2 + ft_word_len(&str[i + 2]);
			word = ft_merge(str, i, &str[j], end - j);
			if (ft_stage_four(&str[i + 2], ft_word_len(&str[i + 2]), &(*token)->left) && !(*token)->left)
				return (ft_throw_syntax_error("<<"));
			if (ft_stage_three(word, ft_strlen(word), &(*token)->right) && (*token)->right)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		else if (!ft_strncmp(&str[i], "<", 1))
		{
			if (ft_add_token(REDIR_IN, "<", token))
				return (EXIT_FAILURE);
			j = i + 1 + ft_word_len(&str[i + 1]);
			word = ft_merge(str, i, &str[j], end - j);
			if (ft_stage_four(&str[i + 1], ft_word_len(&str[i + 1]), &(*token)->left) && !(*token)->left)
				return (ft_throw_syntax_error("<"));
			if (ft_stage_three(word, ft_strlen(word), &(*token)->right) && (*token)->right)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		else if (!ft_strncmp(&str[i], ">", 1))
		{
			if (ft_add_token(REDIR_OUT, ">", token))
				return (EXIT_FAILURE);
			j = i + 1 + ft_word_len(&str[i + 1]);
			word = ft_merge(str, i, &str[j], end - j);
			if (ft_stage_four(&str[i + 1], ft_word_len(&str[i + 1]), &(*token)->left) && !(*token)->left)
				return (ft_throw_syntax_error(">"));
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
			if (ft_add_token(PIPE, "|", token))
				return (EXIT_FAILURE);
			if (ft_stage_three(str, i, &(*token)->left))
			{
				if (!(*token)->left)
					ft_throw_syntax_error("|");
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
			if (ft_add_token(AND, "&&", token))
				return (EXIT_FAILURE);
			if (ft_stage_two(str, i, &(*token)->left))
			{
				if (!(*token)->left)
					ft_throw_syntax_error("&&");
				return (EXIT_FAILURE);
			}
			if (ft_stage_one(&str[i + 2], &(*token)->right))
			{
				if (!(*token)->right)
					ft_throw_syntax_error("newline");
				return (EXIT_FAILURE);
			}
			return (EXIT_SUCCESS);
		}
		else if (!ft_strncmp(&str[i], "||", 2))
		{
			if (ft_add_token(OR, "||", token))
				return (EXIT_FAILURE);
			if (ft_stage_two(str, i, &(*token)->left))
			{
				if (!(*token)->left)
					ft_throw_syntax_error("||");
				return (EXIT_FAILURE);
			}
			if (ft_stage_one(&str[i + 2], &(*token)->right))
			{
				if (!(*token)->right)
					ft_throw_syntax_error("newline");
				return (EXIT_FAILURE);
			}
			return (EXIT_SUCCESS);
		}
		else
			i++;
	}
	return (ft_stage_two(str, i, token));
}
