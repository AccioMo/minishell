/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:20:34 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/19 18:24:38 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_last(char **array)
{
	char	*word;
	int		i;

	i = 0;
	while (array[i])
		i++;
	word = ft_strdup(array[i]);
	ft_free(array);
	return (word);
}

char	*ft_extract_variable(char *word, t_shell *shell)
{
	char	*new_word;
	char	*tmp_word;
	int		i;

	i = 1;
	if (!word)
		return (NULL);
	if (word[i] == '?')
		new_word = ft_realloc(ft_itoa(shell->exit_status), &word[i + 1]);
	else if (word[i] == '_')
	{
		new_word = ft_last(ft_split(ft_getenv("_", shell->env), ' '));
		new_word = ft_realloc(new_word, &word[i + 1]);
	}
	else if (ft_isdigit(word[i]))
		new_word = ft_realloc(ft_strdup(""), &word[i + 1]);
	else
	{
		tmp_word = ft_substr(word, 1, ft_index(&word[i], '$'));
		tmp_word = ft_strtrim(tmp_word, "$");
		tmp_word = ft_realloc(tmp_word, "=");
		//printf("word = %s\n", tmp_word);//waaaaaaaa 3lach khliti hadi hna mni oushiti
		new_word = ft_strdup(ft_getenv(tmp_word, shell->env));
	}
	return (ft_realloc(new_word, ft_strchr(&word[i], '$')));
}

int	ft_late_work(t_token *token, t_shell *shell)
{
	char	*word;
	int		i;

	i = 0;
	if (token->left)
		ft_late_work(token->left, shell);
	if (token->right)
		ft_late_work(token->right, shell);
	if (token->type == WORD)
	{
		while (token->args[i])
		{
			word = ft_strchr(token->args[i], '$');
			while (word)
			{
				word = ft_extract_variable(word, shell);
				token->args[i] = ft_realloc(word, token->args[i]);
				if (!token->args[i])
					return (1);
				word = ft_strchr(token->args[i], '$');
			}
			printf("word = %s\n", token->args[i]);
			i++;
		}
	}
	return (0);
}
