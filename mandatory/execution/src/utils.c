/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:02:05 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/18 16:56:25 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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