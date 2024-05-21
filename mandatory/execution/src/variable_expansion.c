/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:20:34 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/21 19:38:19 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*ft_remove_quotes(char *word)
{
	char	*tmp;

	if (!word)
		return (NULL);
	if (word[0] == '\'')
	{
		tmp = ft_strtrim(word, "\'");
		if (!tmp)
			return (NULL);
		free(word);
		return (tmp);
	}
	else if (word[0] == '\"')
	{
		tmp = ft_strtrim(word, "\"");
		if (!tmp)
			return (NULL);
		free(word);
		return (tmp);
	}
	return (word);
}

char	*ft_expand_vars(char *word, char *value, t_shell *shell)
{
	char * var;

	if (word[0] == '?')
	{
		var = ft_itoa(shell->exit_status);
		if (!var)
			return (NULL);
		value = ft_strjoin(value, var);
		if (!value)
			return (NULL);
		if (word[1] != '\0')
			value = ft_strjoin(value, &word[1]);
		free(var);
	}
	else
	{
		var = ft_strdup(ft_getenv(word, shell->env));
		if (!var)
			return (NULL);
		value = ft_strjoin(value, var);
		if (!value)
			return (NULL);
		free(var);
	}
	return (value);
}

char	*ft_extract_variable(char *word, t_shell *shell)
{
	char	*value;
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = -1;
	// value = ft_substr(word, 0, ft_index(word, '$'));
	value = malloc(sizeof(char) * ft_strlen(word) + 1);
	if (!value)
		return (NULL);
	while (word[i] && word[i] != '$')
	{
		value[i] = word[i];
		i++;
	}
	value[i] = '\0';
	if (word[i] == '$' && word[i + 1] == '\0')
	{
		value[i] = '$';
		value[i + 1] = '\0';
		return (value);
	}
	else
	{
		tmp = ft_split(&word[i + 1], '$');
		if (!tmp)
			return (NULL);
		while (tmp[++j])
		{
			value = ft_expand_vars(tmp[j], value, shell);
			if (tmp[j] == NULL)
				return (ft_free(tmp), NULL);
		}
	}
	return (value);
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
			if (token->args[i][0] != '\'' && token->args[i][0] != '\"' && \
				!ft_strncmp(token->args[i], "*\0", 2))
			{
				token->args = ft_array_delete(token->args, i);
				i += ft_handle_wildecard(token) - 1;
			}
			else if (token->args[i][0] != '\'' && \
				ft_strchr(token->args[i], '$'))
			{
				token->args[i] = ft_extract_variable(token->args[i], shell);
				if (!token->args[i])
					return (1);
			}
			token->args[i] = ft_remove_quotes(token->args[i]);
			i++;
		}
	}
	return (0);
}
