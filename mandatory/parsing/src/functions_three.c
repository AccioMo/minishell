/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:18:26 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/01 19:13:19 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_throw_syntax_error(char *word)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(word, 2);
	ft_putstr_fd("`.\n", 2);
	return (EXIT_FAILURE);
}

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
			i += ft_skip_parentheses(&str[i]) + 1;
		else if (!ft_strncmp(&str[i], ")", 1))
			return (i);
		else
			i++;
	}
	return (i);
}

void	ft_parse_word(char *str, int end, t_token **token)
{
	char	*word;

	word = ft_substr(str, 0, end);
	(*token)->args = ft_cmd_split(word);
	free(word);
	free(str);
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
		new->args[1] = NULL;
		new->args[0] = str;
	}
	*token = new;
	return (new);
}

int	ft_stage_four(char *str, int end, t_token **token)
{
	char	*word;
	int		p;
	int		i;

	i = 0;
	while (str[i] && i < end)
	{
		if (ft_whitespace(str[i]))
			i++;
		else if (!ft_strncmp(&str[i], "(", 1))
		{
			if (!ft_add_token(SUBSHELL, NULL, token))
				return (EXIT_FAILURE);
			p = ft_skip_parentheses(&str[i]);
			while (++p < end)
			{
				if (!ft_whitespace(str[p]))
					return (ft_throw_syntax_error(&str[p]));
			}
			p = ft_skip_parentheses(&str[i]);
			word = ft_substr(&str[i + 1], 0, p - 1);
			ft_stage_one(word, &(*token)->right);
			return (EXIT_SUCCESS);
		}
		else
		{
			p = i;
			if (!ft_add_token(WORD, NULL, token))
				return (EXIT_FAILURE);
			while (p < end)
			{
				if (!ft_strncmp(&str[p], "\"", 1))
					p += ft_index(&str[p + 1], '\"') + 1;
				else if (str[p] == '(')
					return (ft_throw_syntax_error(&str[p]));
				p++;
			}
			word = ft_substr(&str[i], 0, end - i);
			ft_parse_word(word, end, token);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
