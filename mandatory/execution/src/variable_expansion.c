/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:20:34 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/22 22:56:18 by mzeggaf          ###   ########.fr       */
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

char	*ft_expand_variable(char *str, int *i, t_shell *shell)
{
	char	*tmp;
	char	*new;
	int		len;

	if (ft_isdigit(*str) && (*i)++)
		return (NULL);
	else if (*str == '?' && (*i)++)
		return (ft_itoa(shell->exit_status));
	else if (*str == '_' && (*i)++)
		return (ft_strdup(ft_getenv("_", shell->env)));
	else
	{
		len = 0;
		while (str[len] && str[len] != '$' && str[len] != '\'' \
				&& str[len] != '\"' && !ft_whitespace(str[len]))
			len++;
		tmp = ft_substr(str, 0, len);
		new = ft_getenv(tmp, shell->env);
		free(tmp);
		*i += len;
		return (ft_strdup(new));
	}
}

char	*ft_extraction(char *str, t_shell *shell)
{
	char	*tmp;
	char	*new;
	int		len;
	int		i;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = ft_expand_variable(&str[++i], &i, shell);
			new = ft_realloc(new, tmp);
			free(tmp);
		}
		else
		{
			len = ft_index(&str[i], '$');
			tmp = ft_substr(str, i, len);
			new = ft_realloc(new, tmp);
			free(tmp);
			i += len;
		}
	}
	return (new);
}

char	*ft_strrem(char *str, char to_remove)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str)));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] == to_remove)
			i++;
		new[j++] = str[i++];
	}
	new[j] = '\0';
	return (new);
}

int	ft_contains_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i += ft_index(&str[i + 1], '\'');
		else if (str[i] == '\"')
		{
			while (str[++i] && str[i] != '\"')
			{
				if (str[i] == '$')
					return (1);
			}
		}
		else if (str[i] == '$' && str[i + 1] != '\0')
			return (1);
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
		while (token->args[i])
		{
			if (!ft_strncmp(token->args[i], "*\0", 2))
			{
				token->args = ft_array_delete(token->args, i);
				i += ft_handle_wildecard(token);
				continue ;
			}
			if (ft_contains_variable(token->args[i]))
			{
				token->args[i] = ft_extraction(token->args[i], shell);
				if (!token->args[i])
					return (1);
			}
			if (ft_strchr(token->args[i], '\"') || ft_strchr(token->args[i], '\''))
				token->args[i] = ft_remove_quotes(token->args[i]);
			i++;
		}
	}
	return (0);
}
