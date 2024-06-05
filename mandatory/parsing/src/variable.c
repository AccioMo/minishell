/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:17:30 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/05 21:32:20 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*ft_expand_variable(char *str, int *i, t_shell *shell)
{
	char	*tmp;
	char	*new;
	int		len;

	if (ft_isdigit(*str) && (*i)++)
		return (ft_strdup(""));
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

// static char	*ft_replace_variable(char *str, t_token *token, t_shell *shell)
// {
// 	char	*tmp;
// 	char	*new;
// 	int		len;
// 	int		i;

// 	i = 0;
// 	new = ft_strdup("");
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 			i = ft_index(&str[i + 1], '\'') + 1;
// 		else if (str[i] == '\"')
// 		{
// 			i++;
// 			while (str[i] && str[i] != '\"')
// 			{
// 				if (str[i] == '$')
// 				{
// 					tmp = ft_expand_variable(&str[++i], &i, shell);
// 					new = ft_realloc(new, tmp);
// 					free(tmp);
// 				}
// 				else
// 				{
// 					len = ft_index(&str[i], '$');
// 					tmp = ft_substr(str, i, len);
// 					new = ft_realloc(new, tmp);
// 					free(tmp);
// 					i += len;
// 				}
// 			}
// 		}
// 		else if (str[i] == '$')
// 		{
// 			tmp = ft_expand_variable(&str[++i], &i, shell);
// 			char ** new_args = ft_split(tmp, ' ');
// 			int j = 0;
// 			while (new_args[j])
// 			{
// 				token->args = ft_append_to_array(token->args, new_args[j]);
// 				j++;
// 			}
// 			free(tmp);
// 		}
// 		else
// 		{
// 			len = ft_index(&str[i], '$');
// 			tmp = ft_substr(str, i, len);
// 			new = ft_realloc(new, tmp);
// 			free(tmp);
// 			i += len;
// 		}
// 	}
// 	return (new);
// }

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

int	ft_variables(t_token *token, t_shell *shell, int num)
{
	char	*tmp;
	char	*new;
	char	*str;
	int		len;
	int		i;

	i = 0;
	str = ft_strdup(token->args[num]);
	token->args = ft_remove_from_array(token->args, num);
	while (str[i])
	{
		if (str[i] == '\'')
			i = ft_index(&str[i + 1], '\'') + 1;
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				if (str[i] == '$')
				{
					tmp = ft_expand_variable(&str[++i], &i, shell);
					token->args = ft_append_to_array(token->args, tmp);
					// free(tmp);
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
			printf("tmp = %s\n", tmp);
			char	**new_args = ft_split(tmp, ' ');
			if (!new_args)
				return (0);
			int	j = 0;
			while (new_args[j])
			{
				token->args = ft_append_to_array(token->args, new_args[j]);
				j++;
			}
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
	i = 0;
	while (token->args[i])
	{
		printf("token->args[i] = %s\n", token->args[i++]);
	}
	printf("the end\n");
	if (!token->args[i])
		return (1);
	return (0);
}
