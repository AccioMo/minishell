/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_wildcard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:21:02 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/11 16:47:04 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_replace_wildcard(char *str, int i)
{
	char	*tmp;
	char	*tmp_str;

	tmp = ft_strjoin("\\*", &str[i]);
	tmp_str = ft_substr(str, 0, i - 1);
	tmp_str = ft_realloc(tmp_str, tmp);
	free(tmp);
	free(str);
	return (tmp_str);
}

char	*ft_quoted_wildcard(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] && str[i] != '\'')
				;
		}
		else if (str[i] == '\"')
		{
			while (str[++i] && str[i] != '\"')
				;
		}
		else if (str[i] == '*')
			str = ft_replace_wildcard(str, ++i);
		i++;
	}
	return (str);
}

char	*ft_remove_wd_backslash(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "\\*", 2))
		{
			tmp = ft_substr(str, 0, i);
			tmp = ft_realloc(tmp, &str[i + 1]);
			free(str);
			str = tmp;
		}
		i++;
	}
	return (str);
}
