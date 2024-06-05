/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:20:34 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/05 21:10:11 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	if (!word)
		return (NULL);
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

int	ft_handle_tilde(t_token *token, int i, t_shell *shell)
{
	char	*home;
	char	*new;

	home = ft_getenv("HOME", shell->env);
	if (!home)
		return (0);
	new = ft_strjoin(home, token->args[i] + 1);
	free(token->args[i]);
	token->args[i] = new;
	return (0);
}

// if (token->left)
// 	ft_expand(token->left, shell);
// if (token->right)
// 	ft_expand(token->right, shell);
// if (token->type == WORD)
// }
// {

int	ft_expand(t_token *token, t_shell *shell)
{
	int	i;

	i = 0;
	while (token->args[i])
	{
		if (ft_contains_variable(token->args[i]))
			i += ft_variables(token, shell, i);
		else if (ft_found_token(token->args[i], '*'))
			i += ft_wildcard(token, i);
		else if (ft_found_token(token->args[i], '~'))
			i += ft_handle_tilde(token, i, shell);
		else
			token->args[i] = ft_remove_quotes(token->args[i]);
		i++;
	}
	return (0);
}
