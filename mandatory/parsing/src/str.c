/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:22:50 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/22 19:09:07 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_arg_count(char *str)
{
	int	ac;

	ac = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
		}
		if (*str == '\"')
		{
			str++;
			while (*str && *str != '\"')
				str++;
		}
		if (!ft_whitespace(str[0]) && (ft_whitespace(str[1]) || !str[1]))
			ac++;
		str++;
	}
	return (ac);
}

static int	ft_arg_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && !ft_whitespace(str[len]))
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

static char	*ft_get_arg(char **array, char *str)
{
	int	len;

	len = 0;
	while (ft_whitespace(*str))
		str++;
	len = ft_arg_len(str);
	*array = ft_substr(str, 0, len);
	if (!*array)
		return (NULL);
	return (str + len);
}

char	**ft_cmd_split(char *str)
{
	char	**array;
	int		arg_count;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	arg_count = ft_arg_count(str);
	array = (char **)malloc((arg_count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array[arg_count] = NULL;
	while (i < arg_count)
	{
		str = ft_get_arg(array + i, str);
		if (!str)
		{
			ft_free(array);
			return (NULL);
		}
		i++;
	}
	return (array);
}
