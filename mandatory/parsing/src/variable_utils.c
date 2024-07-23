/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:20:34 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/22 23:13:16 by mzeggaf          ###   ########.fr       */
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
		if (*str)
			str++;
	}
	return (len);
}

static char	*ft_remove_quotes(char *str)
{
	char	*word;
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	word = (char *)malloc(sizeof(char) * (ft_arg_len(str) + 1));
	if (!word)
		return (NULL);
	while (str[j] && !ft_whitespace(*str))
	{
		if (str[j] == '\"')
			while (str[++j] && str[j] != '\"')
				word[i++] = str[j];
		else if (str[j] == '\'')
			while (str[++j] && str[j] != '\'')
				word[i++] = str[j];
		else
			word[i++] = str[j];
		j++;
	}
	word[i] = '\0';
	return (free(str), word);
}

char	*ft_handle_tilde(char *tilde, t_shell *shell)
{
	char	*home;
	char	*new;

	if (tilde[1] == '/' || tilde[1] == '\0')
	{
		home = ft_getenv("HOME", shell->env);
		if (!home)
			return (NULL);
		new = ft_strjoin(home, tilde + 1);
		if (!new)
			return (NULL);
		free(tilde);
		return (new);
	}
	return (tilde);
}

int	ft_expand_variables(t_token *token, t_shell *shell)
{
	char	**old_args;
	int		i;

	i = 0;
	if (!token->args)
		return (0);
	old_args = token->args;
	token->args = NULL;
	while (old_args[i])
	{
		if (ft_contains_variable(old_args[i]))
			ft_variables(old_args[i], token, shell);
		else
		{
			if (old_args[i][0] == '~')
				old_args[i] = ft_handle_tilde(old_args[i], shell);
			old_args[i] = ft_backslash_wildcard(old_args[i]);
			old_args[i] = ft_remove_quotes(old_args[i]);
			token->args = ft_append_to_array(token->args, old_args[i]);
		}
		i++;
	}
	ft_free(old_args);
	return (0);
}

int	ft_expand_wildcard(t_token *token)
{
	char	**old_args;
	int		i;

	i = 0;
	if (!token->args)
		return (0);
	old_args = token->args;
	token->args = NULL;
	while (old_args[i])
	{
		if (ft_strstr(old_args[i], "\\*"))
			ft_wildcard(old_args[i], token);
		else
		{
			old_args[i] = ft_remove_wd_backslash(old_args[i]);
			token->args = ft_append_to_array(token->args, old_args[i]);
		}
		i++;
	}
	ft_free(old_args);
	return (0);
}
