/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:17:30 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/06 09:52:53 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*ft_expand_variable(char *str, int *i, t_shell *shell)
{
	char	*tmp;
	char	*new;
	int		len;

	while (*str && *str == '$' && ++(*i))
		str++;
	if (ft_isdigit(*str) && (*i)++)
		return (ft_strdup(""));
	else if (*str == '?' && (*i)++)
		return (ft_itoa(shell->exit_code));
	else if (*str == '_' && (*i)++)
		return (ft_strdup(ft_getenv("_", shell->env)));
	else
	{
		len = 0;
		while (str[len] && ft_isalnum(str[len]))
			len++;
		if (len == 0 && str[len] != '\'' && str[len] != '\"')
			return (ft_strdup("$"));
		tmp = ft_substr(str, 0, len);
		new = ft_getenv(tmp, shell->env);
		free(tmp);
		*i += len;
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

int	ft_variables(char *str, t_token *token, t_shell *shell)
{
	char	*tmp;
	char	*new;
	int		len;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	new = NULL;
	ret--;
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
			i++;
			while (str[i])
			{
				if (str[i] == '\"')
				{
					i++;
					break ;
				}
				if (str[i] == '$')
				{
					tmp = ft_expand_variable(&str[++i], &i, shell);
					if (tmp[0] == '\0')
						new = ft_realloc(new, "$");
					else
						new = ft_realloc(new, tmp);
					free(tmp);
				}
				else
				{
					len = ft_index(&str[i], '$');
					int len2 = ft_index(&str[i], '\"');
					if (len2 < len)
						len = len2;
					tmp = ft_substr(str, i, len);
					new = ft_realloc(new, tmp);
					free(tmp);
					i += len;
				}
			}
		}
		else if (str[i] == '$')
		{
			tmp = ft_expand_variable(&str[++i], &i, shell);
			char	**new_args = ft_split(tmp, ' ');
			free(tmp);
			if (!new_args || !new_args[0])
				continue ;
			int	arr_len = ft_array_len(new_args);
			// printf("arr_len = %d\n", arr_len);
			new = ft_realloc(new, new_args[0]);
			if (arr_len == 1)
				continue ;
			token->args = ft_append_to_array(token->args, new);
			new_args++;
			ret++;
			free(new);
			new = NULL;
			int	k = 1;
			while (k < (arr_len - 1))
				token->args = ft_append_to_array(token->args, new_args[k++]);
			new = ft_strdup(new_args[k]);
			ret += (arr_len - 1);
			free(tmp);
		}
		else
		{
			tmp = ft_substr(str, i, 1);
			new = ft_realloc(new, tmp);
			i++;
		}
	}
	if (new)
	{
		token->args = ft_append_to_array(token->args, new);
		ret++;
	}
	// var_cmd = ft_split(token->args[i], ' ');
	// token->args = ft_remove_from_array(token->args, i);
	// while (var_cmd[variables])
	// {
	// 	if (ft_found_token(var_cmd[variables], '*'))
	// 		wildcards += ft_handle_wildecard(token, var_cmd[variables]);
	// 	else
	// 		token->args = ft_append_to_array(token->args, var_cmd[variables]);
	// 	variables++;
	// }
	// printf("ret = %d\n", ret);
	return (ret);
}
