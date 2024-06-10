/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:17:30 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/10 21:37:18 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_variable_length(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] == '$')
		len++;
	if (ft_isdigit(str[len]))
		len++;
	else if (str[len] == '?')
		len++;
	else if (str[len] == '_')
		len++;
	else
		while (str[len] && ft_isalnum(str[len]))
			len++;
	return (len);
}

static char	*ft_expand_variable(char *str, t_shell *shell)
{
	char	*tmp;
	char	*new;
	int		len;

	while (*str && *str == '$')
		str++;
	if (ft_isdigit(*str))
		return (ft_strdup(""));
	else if (*str == '?')
		return (ft_itoa(shell->exit_code));
	else if (*str == '_')
		return (ft_strdup(ft_getenv("_", shell->env)));
	else
	{
		len = 0;
		while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
			len++;
		if (len == 0 && str[len] != '\'' && str[len] != '\"')
			return (ft_strdup("$"));
		tmp = ft_substr(str, 0, len);
		new = ft_getenv(tmp, shell->env);
		free(tmp);
		return (ft_strdup(new));
	}
}

int	ft_contains_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i += ft_index(&str[i + 1], '\'') + 1;
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

char	*ft_quoted_variables(char *str, t_shell *shell)
{
	char	*tmp;
	char	*new;

	new = NULL;
	while (*str && *str != '\"')
	{
		if (*str == '$')
		{
			tmp = ft_expand_variable(++str, shell);
			new = ft_realloc(new, tmp);
			free(tmp);
			str += ft_variable_length(str);
		}
		else
		{
			tmp = ft_substr(str, 0, 1);
			new = ft_realloc(new, tmp);
			str++;
		}
	}
	return (new);
}

char	*ft_split_variable(char *str, char *new, t_token *token, t_shell *shell)
{
	char	**new_args;
	int		arr_len;
	char	*tmp;
	int		k;

	k = 0;
	tmp = ft_expand_variable(++str, shell);
	new_args = ft_split(tmp, ' ');
	free(tmp);
	if (!new_args || !new_args[0])
		return (NULL);
	arr_len = ft_array_len(new_args);
	new = ft_realloc(new, new_args[0]);
	if (ft_strchr(new, '*'))
		return (ft_wildcard(new, token, shell));
	if (arr_len == 1)
		return (new);
	token->args = ft_append_to_array(token->args, new);
	free(new);
	new = NULL;
	while (++k < (arr_len - 1))
	{
		if (ft_strchr(new_args[k], '*'))
			ft_wildcard(new_args[k], token, shell);
		else
			token->args = ft_append_to_array(token->args, new_args[k]);
	}
	new = ft_strdup(new_args[k]);
	ft_free(new_args);
	return (new);
}

int	ft_next_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] != '\"' && str[i] != '\'')
		i++;
	return (i);
}

int	ft_variables(char *str, t_token *token, t_shell *shell)
{
	char	*tmp;
	char	*new;
	int		len;
	int		v;
	int		i;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			tmp = ft_substr(str, i + 1, ft_index(&str[i + 1], '\''));
			new = ft_realloc(new, tmp);
			i += ft_index(&str[i + 1], '\'') + 2;
		}
		else if (str[i] == '\"')
		{
			len = ft_index(&str[++i], '\"') + 1;
			tmp = ft_quoted_variables(&str[i], shell);
			new = ft_realloc(new, tmp);
			i += len;
		}
		else if (str[i] == '$')
		{
			new = ft_split_variable(&str[i], new, token, shell);
			i += ft_variable_length(&str[i]);
		}
		else
		{
			v = ft_next_variable(&str[i]);
			tmp = ft_substr(str, i, v);
			new = ft_realloc(new, tmp);
			i += v;
		}
	}
	if (new)
	{
		if (ft_found_token(new, '*'))
			ft_wildcard(new, token, shell);
		else
			token->args = ft_append_to_array(token->args, new);
	}
	return (0);
}
