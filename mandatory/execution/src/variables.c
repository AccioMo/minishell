/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:17:30 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/25 19:58:15 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

static char	*ft_expand_variable(char *str, int *i, t_shell *shell)
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

static char	*ft_find_variable(char *str, t_shell *shell)
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

static int	ft_contains_variable(char *str)
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

int	ft_variables(t_token *token, t_shell *shell)
{
	char	**arg;
	int		variables;
	int		i;
	int		j;

	i = 0;
	variables = 0;
	while (token->args[i])
	{
		if (ft_contains_variable(token->args[i]))
		{
			j = 0;
			variables++;
			token->args[i] = ft_remove_quotes(token->args[i]);
			token->args[i] = ft_find_variable(token->args[i], shell);
			arg = ft_cmd_split(token->args[i]);
			token->args = ft_array_delete(token->args, i);
			while (arg[j])
			{
				token->args = ft_append_to_array(token->args, arg[j]);
				j++;
			}
			i += j;
			if (!token->args[i])
				return (-1);
		}
		else if ((ft_strncmp(token->args[i], "\"*\"\0", 4) \
				|| ft_strncmp(token->args[i], "\'*\'\0", 4)) \
				&& (ft_strchr(token->args[i], '\'') \
				&& ft_strchr(token->args[i], '\"')))
			token->args[i] = ft_remove_quotes(token->args[i]);
		i++;
	}
	return (variables);
}
