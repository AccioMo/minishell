/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 00:09:12 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/21 20:24:25 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_handle_wildcard(char *pattern, int *i, char **str)
{
	char	*tmp_str;

	tmp_str = *str;
	if (ft_strncmp(tmp_str, pattern, *i))
		return (NULL);
	pattern += *i;
	while (!ft_strncmp(pattern, "\\*", 2))
		pattern += 2;
	if (!ft_strstr(pattern, "\\*"))
	{
		if (ft_strlen(pattern) > ft_strlen(tmp_str))
			return (NULL);
		tmp_str += (ft_strlen(tmp_str) - ft_strlen(pattern));
		*str = tmp_str;
		*i = 0;
		return (pattern);
	}
	while (*tmp_str && *tmp_str != *pattern)
		tmp_str++;
	*i = 0;
	*str = tmp_str;
	return (pattern);
}

char	*ft_single_quotes_wildcard(char *pattern, int i)
{
	char	*tmp;
	int		pe;

	pe = ft_index(&pattern[i + 1], "\'") + 1;
	tmp = ft_substr(&pattern[i + 1], 0, pe);
	pattern = ft_substr(pattern, i, pe);
	pattern = ft_realloc(pattern, tmp);
	free(tmp);
	return (pattern);
}

char	*ft_wildcard_match(char *pattern, char *str)
{
	int		i;

	i = 0;
	while (pattern[i])
	{
		if (!ft_strncmp(&pattern[i], "\\*", 2))
			pattern = ft_handle_wildcard(pattern, &i, &str);
		else
			i++;
		if (!pattern)
			return (0);
	}
	if (str && ft_strncmp(str, pattern, i))
		return (0);
	return (pattern);
}

int	ft_found_token(char *str, char c)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '\"')
			j += ft_index(&str[j + 1], "\"") + 1;
		else if (str[j] == '\'')
			j += ft_index(&str[j + 1], "\'") + 1;
		else if (str[j] == c)
			return (1);
		j++;
	}
	return (0);
}
