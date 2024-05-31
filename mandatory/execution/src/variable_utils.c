/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:20:34 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/25 19:28:46 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	ft_arg_len(char *str)
{
	int	len;

	len = 0;
	while (*str && !ft_whitespace(*str))
	{
		if (*str == '\"')
			while (*++str && *str != '\"')
				len++;
		else if (*str == '\'')
			while (*++str && *str != '\'')
				len++;
		else
			len++;
		str++;
	}
	return (len);
}

char	*ft_remove_quotes(char *str)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (ft_arg_len(str) + 1));
	while (*str && !ft_whitespace(*str))
	{
		if (*str == '\"')
			while (*++str && *str != '\"')
				word[i++] = *str;
		else if (*str == '\'')
			while (*++str && *str != '\'')
				word[i++] = *str;
		else
			word[i++] = *str;
		str++;
	}
	word[i] = '\0';
	return (word);
}

int	ft_quotes(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '\"') || ft_strchr(args[i], '\''))
			args[i] = ft_remove_quotes(args[i]);
		i++;
	}
	return (0);
}

int	ft_expand(t_token *token, t_shell *shell)
{
	int	i;

	i = 0;
	if (token->left)
		ft_expand(token->left, shell);
	if (token->right)
		ft_expand(token->right, shell);
	if (token->type == WORD)
	{
		ft_variables(token, shell);
		ft_wildcard(token);
		i++;
	}
	return (0);
}