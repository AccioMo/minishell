/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:20:34 by zouddach           #+#    #+#             */
/*   Updated: 2024/05/21 07:36:10 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
	int 	i;
	int 	j;
	char	*value;
	char	**tmp;

	i = 0;
	j = -1;
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
	int		i;

	i = 0;
	if (token->left)
		ft_expand(token->left, shell);
	if (token->right)
		ft_expand(token->right, shell);
	if (token->type == WORD)
	{
		while (token->args[i])
		{
			if (token->args[i][0] == '*' && token->args[i][1] == '\0')
			{
				ft_handle_wildecard(token, i);
				ft_realoccate_args(&token->args, i);
				i++;
				continue ;
			}
			if (!ft_strchr(token->args[i], '$'))
			{
				i++;
				continue ;
			}
			token->args[i] = ft_extract_variable(token->args[i], shell);
			if (!token->args[i])
				return (1);//malloc error
			i++;
		}
	}
	return (0);
}
