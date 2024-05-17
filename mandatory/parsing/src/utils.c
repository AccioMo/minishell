/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:15:58 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/16 21:36:10 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_whitespace(char c)
{
	return (c == ' ' || c == 127 || (c >= 9 && c <= 13));
}

int	ft_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_rev_index(char *str, char c)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (0);
}

static int	ft_reserved_word(char *str)
{
	if (!ft_strncmp(str, "||", 2))
		return (1);
	if (!ft_strncmp(str, "&&", 2))
		return (1);
	if (!ft_strncmp(str, "|", 1))
		return (1);
	if (!ft_strncmp(str, ">", 1))
		return (1);
	if (!ft_strncmp(str, ">>", 2))
		return (1);
	if (!ft_strncmp(str, "<", 1))
		return (1);
	if (!ft_strncmp(str, "<<", 2))
		return (1);
	if (!ft_strncmp(str, "(", 1))
		return (1);
	if (!ft_strncmp(str, ")", 1))
		return (1);
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
	while (str[len] && !ft_whitespace(str[len]) && !ft_reserved_word(&str[len]))
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

char	*ft_merge(char *part_one, int limit_one, char *part_two, int limit_two)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	len = limit_one + limit_two + 1;
	new = (char *)malloc(sizeof(char) * (len));
	ft_strlcpy(new, part_one, limit_one + 1);
	ft_strlcat(new, part_two, len);
	return (new);
}
