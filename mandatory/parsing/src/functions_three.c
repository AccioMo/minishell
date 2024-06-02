/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:18:26 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/01 18:23:47 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_throw_error(char *msg, char *word)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" `", 2);
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
			i += ft_skip_parentheses(&str[i]);
		else if (!ft_strncmp(&str[i], ")", 1))
			return (i);
		else
			i++;
	}
	return (i);
}

int	ft_parse_word(char *str, int end, t_token **token)
{
	char	*word;

	word = ft_substr(str, 0, end);
	if (!ft_add_token(WORD, NULL, token))
		return (EXIT_FAILURE);
	(*token)->args = ft_cmd_split(word);
	if ((*token)->args == NULL)
		return (EXIT_FAILURE);
	free(word);
	free(str);
	return (EXIT_SUCCESS);
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
			if (ft_stage_one(word, &(*token)->right))
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		else
		{
			word = ft_substr(&str[i], 0, end - i);
			if (!word)
				return (EXIT_FAILURE);
			if (ft_parse_word(word, end, token))
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
