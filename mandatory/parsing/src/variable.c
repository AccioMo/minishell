/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:17:30 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/04 06:01:11 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*ft_expand_variable(char *str, int *i, t_shell *shell)
{
	char	*tmp;
	char	*new;
	int		len;

	if (ft_isdigit(*str) && (*i)++)
		return (NULL);
	else if (*str == '?' && (*i)++)
		return (ft_itoa(shell->exit_code));
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

static char	*ft_replace_variable(char *str, t_shell *shell)
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

int	ft_variables(t_token *token, t_shell *shell, int i)
{
	char	**var_cmd;
	int		j;
	int		k;

	j = 0;
	k = 0;
	token->args[i] = ft_replace_variable(token->args[i], shell);
	var_cmd = ft_cmd_split(token->args[i]);
	token->args = ft_remove_from_array(token->args, i);
	while (var_cmd[j])
	{
		if (ft_found_wildcard(var_cmd[j]))
			k += ft_handle_wildecard(token, var_cmd[j]);
		else
			token->args = ft_append_to_array(token->args, var_cmd[j]);
		j++;
	}
	i += j;
	if (!token->args[i])
		return (-1);
	if (ft_array_len(&token->args[i]) == 1 || token->args[i][0] == '\"')
		token->args[i] = ft_remove_quotes(token->args[i]);
	return (i - 1);
}
