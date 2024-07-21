/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:58:26 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/07/21 20:23:29 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_next_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] != '\"' && str[i] != '\'')
		i++;
	return (i);
}

static char	*ft_not_variable(char *str, int *i, char *new)
{
	char	*tmp;
	int		v;

	v = ft_next_variable(&str[*i]);
	tmp = ft_substr(str, *i, v);
	tmp = ft_var_backslash_wildcard(tmp);
	new = ft_realloc(new, tmp);
	free(tmp);
	*i += v;
	return (new);
}

static char	*ft_variable_skip_quotes(char *str, char *new, int *i, t_shell *sh)
{
	char	*tmp;
	int		len;

	if (str[*i] == '\'')
	{
		*i += 1;
		tmp = ft_substr(str, *i, ft_index(&str[*i], "\'"));
		new = ft_realloc(new, tmp);
		free(tmp);
		*i += ft_index(&str[*i], "\'") + 1;
	}
	else if (str[*i] == '\"')
	{
		*i += 1;
		len = ft_index(&str[*i], "\"") + 1;
		tmp = ft_quoted_variables(&str[*i], sh);
		new = ft_realloc(new, tmp);
		free(tmp);
		*i += len;
	}
	return (new);
}

int	ft_variables(char *str, t_token *token, t_shell *shell)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			new = ft_variable_skip_quotes(str, new, &i, shell);
		else if (str[i] == '$')
		{
			while (str[i] && str[i] == '$')
				i++;
			new = ft_split_variable(&str[i], new, token, shell);
			i += ft_variable_length(&str[i]);
		}
		else
			new = ft_not_variable(str, &i, new);
	}
	if (new)
		token->args = ft_append_to_array(token->args, new);
	free(new);
	return (0);
}
