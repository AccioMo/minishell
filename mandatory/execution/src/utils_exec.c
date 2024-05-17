/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:02:05 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/16 22:07:36 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	*ft_get_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*ft_getenv(char *name, char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		if (ft_strncmp(arr[i], name, ft_strlen(name)) == 0)
			return (*(arr + i) + ft_strlen(name) + 1);
		i++;
	}
	return (NULL);
}

int	ft_two_d_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}