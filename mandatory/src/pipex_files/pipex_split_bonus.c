/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:47:41 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/26 15:44:58 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_sep(char c, char sep)
{
	if ((c == '\0' || c == sep))
		return (1);
	else
		return (0);
}

static int	ft_arg_count(char *str, char c)
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
		if (!ft_sep(*str, c) && ft_sep(*(str + 1), c) && *str != '\\')
			ac++;
		str++;
	}
	return (ac);
}

static int	ft_arg_len(int *quotes, char *str, char c)
{
	int	len;

	len = 0;
	while (!ft_sep(*(str + len), c))
	{
		if (*(str + len) == '\\' && *(str + len + 1))
			len++;
		if (*(str + len) == '\'')
		{
			len++;
			quotes++;
			while (*(str + len) && *(str + len) != '\'')
				len++;
		}
		if (*(str + len) == '\"')
		{
			len++;
			quotes++;
			while (*(str + len) && *(str + len) != '\"')
				len++;
		}
		len++;
	}
	return (len);
}

static char	*ft_get_arg(char **array, char *str, char c)
{
	int	len;
	int	quotes;

	len = 0;
	quotes = 0;
	while (*str && ft_sep(*str, c))
		str++;
	len = ft_arg_len(&quotes, str, c);
	*array = (char *)malloc((len + 1) * sizeof(char));
	if (!*array)
		return (NULL);
	ft_cmd_cpy(*array, str, len - (quotes * 2));
	while (!ft_sep(*(str + len), c))
		len++;
	return (str + len);
}

char	**ft_cmd_split(char *str, char c)
{
	char	**array;
	int		ac;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	ac = ft_arg_count(str, c);
	array = (char **)malloc((ac + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	*(array + ac) = NULL;
	while (i < ac)
	{
		str = ft_get_arg(array + i, str, c);
		if (!str)
		{
			ft_free(array);
			return (NULL);
		}
		i++;
	}
	return (array);
}
