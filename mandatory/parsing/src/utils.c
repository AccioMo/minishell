/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:15:58 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/09 21:28:58 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_rindex(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (0);
}

int	ft_word_len(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] && ft_whitespace(str[len]))
		len++;
	while (str[len] && !ft_whitespace(str[len]))
		len++;
	return (len);
}

char	*ft_first_word(char *str)
{
	int		i;
	char	*word;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && ft_whitespace(str[i]))
		i++;
	word = ft_substr(str, i, ft_word_len(&str[i]));
	return (word);
}

char	*ft_append_token(char *word, char **args)
{
}
