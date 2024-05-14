/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:22:50 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/11 19:23:02 by mzeggaf          ###   ########.fr       */
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
	while (*str && !ft_whitespace(*str))
	{
		if (*str == '\"')
			while (*++str && *str != '\"')
				len++;
		if (*str == '\'')
			while (*++str && *str != '\'')
				len++;
		len++;
		str++;
	}
	return (len);
}

static char	*ft_cmd_cpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (*src == '\"')
			while (*++src && *src != '\"')
				dst[i++] = *src;
		else if (*src == '\'')
			while (*++src && *src != '\'')
				dst[i++] = *src;
		else
			dst[i++] = *src++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_get_arg(char **array, char *str)
{
	int	len;

	len = 0;
	while (ft_whitespace(*str))
		str++;
	len = ft_arg_len(str);
	*array = (char *)malloc((len + 1) * sizeof(char));
	if (!*array)
		return (NULL);
	ft_cmd_cpy(*array, str, len);
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