/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:15:58 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/07/21 20:22:38 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_whitespace(char c)
{
	return (c == ' ' || c == 127 || (c >= 9 && c <= 13));
}

int	ft_index(char *str, char *c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == *c)
			return (i);
		i++;
	}
	if (str[i] == '\0')
		ft_throw_syntax_error(c);
	return (i);
}

int	ft_reserved_word(char *str)
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
	{
		if (str[len] == '\"')
			while (str[++len] && str[len] != '\"')
				;
		if (str[len] == '\'')
			while (str[++len] && str[len] != '\'')
				;
		len++;
	}
	return (len);
}

char	*ft_merge(char *part_one, int limit_one, char *part_two, int limit_two)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	len = limit_one + limit_two + 1;
	new = (char *)malloc(sizeof(char) * (len));
	if (!new)
		return (NULL);
	ft_strlcpy(new, part_one, limit_one + 1);
	ft_strlcat(new, part_two, len);
	return (new);
}
