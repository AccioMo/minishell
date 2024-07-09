/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 00:24:18 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/07/10 00:25:05 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*ft_split_variable_util(char **new_args, t_token *token)
{
	char	*new;
	int		arr_len;
	int		k;

	k = 0;
	arr_len = ft_array_len(new_args);
	new = NULL;
	while (++k < (arr_len - 1))
	{
		new_args[k] = ft_var_backslash_wildcard(new_args[k]);
		token->args = ft_append_to_array(token->args, new_args[k]);
	}
	new = ft_strdup(new_args[k]);
	ft_free(new_args);
	return (new);
}

char	*ft_split_variable(char *str, char *new, t_token *token, t_shell *shell)
{
	char	**new_args;

	str = ft_expand_variable(str, shell);
	if (!str)
		return (new);
	new_args = ft_split(str, ' ');
	if (!new_args)
		return (new);
	if (!new_args[0])
	{
		ft_free(new_args);
		return (new);
	}
	ft_array_len(new_args);
	new = ft_realloc(new, new_args[0]);
	new = ft_var_backslash_wildcard(new);
	if (ft_array_len(new_args) == 1)
	{
		ft_free(new_args);
		return (new);
	}
	token->args = ft_append_to_array(token->args, new);
	free(new);
	return (ft_split_variable_util(new_args, token));
}
