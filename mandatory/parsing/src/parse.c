/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:29:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/06 16:54:45 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// use recursion for parantheses

int	ft_whitespace(char c)
{
	return (c == ' ' || c == 127 || c == 0 || (c >= 9 && c <= 13));
}

char	*ft_cp_word(char *str)
{
	char	*word;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (ft_whitespace(str[len]))
		len++;
	while (!ft_whitespace(str[len]))
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	while (!ft_whitespace(str[i]))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	ft_word_len(char *str)
{
	int	len;

	len = 0;
	while (!ft_whitespace(str[len]))
		len++;
	return (len);
}

int	ft_parse_redir_in(char *line, t_env *env)
{
	t_token	*token;
	int		len;
	int		i;

	i = 0;
	if (!env->root)
	{
		env->root = (t_token *)malloc(sizeof(t_token));
		token = env->root;
	}
	else
	{
		token = env->root;
		while (token->right)
			token = token->right;
		token->right = (t_token *)malloc(sizeof(t_token));
		token = token->right;
	}
	token->args = (char **)malloc(sizeof(char *) * 3);
	token->args[2] = NULL;
	if (*line != '<')
		token->args[0] = "<";
	else
		token->args[i++] = "<<";
	while (ft_whitespace(line[i]))
		i++;
	len = ft_word_len(&line[i]);
	token->args[1] = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(token->args[1], &line[i], len + 1);
	return (len + i);
}

int	ft_parse(char *line, t_env *env)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '<')
			i = ft_parse_redir_in(&line[++i], env);
		// else if (line[i] == '>')
		// 	i = ft_parse_redir_out(&line[++i], env);
		// else if (line[i] == '|')
		// 	i = ft_parse_pipe(&line[i], env);
		else
			i++;
	}
	i = 0;
	while (env->root->args[i])
		printf("args: %s\n", env->root->args[i++]);
}
