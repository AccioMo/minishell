/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:47:41 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/09 19:08:16 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_separator(char c, char sep)
{
	if (c == '\0' || c == sep)
		return (1);
	else
		return (0);
}

static int	ft_word_count(char *str, char c)
{
	int	wc;

	wc = 0;
	while (*str)
	{
		if (!ft_separator(*str, c) && ft_separator(*(str + 1), c))
			wc++;
		str++;
	}
	return (wc);
}

static char	*ft_get_word(char **array, char *str, char c)
{
	int	len;

	len = 0;
	while (ft_separator(*str, c))
		str++;
	while (!ft_separator(*(str + len), c))
		len++;
	*array = (char *)malloc((len + 1) * sizeof(char));
	ft_strlcpy(*array, str, len + 1);
	if (!*array)
		return (NULL);
	return (str + len);
}

static void	ft_free(char **ptr)
{
	char	**hold;

	hold = ptr;
	if (!ptr)
		return ;
	while (*ptr)
		free(*ptr++);
	free(hold);
}

char	**ft_split(char *str, char c)
{
	char	**array;
	int		wc;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	wc = ft_word_count(str, c);
	array = (char **)malloc((wc + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	*(array + wc) = NULL;
	while (i < wc)
	{
		str = ft_get_word(array + i, str, c);
		if (!str)
		{
			ft_free(array);
			return (NULL);
		}
		i++;
	}
	return (array);
}
