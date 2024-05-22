/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 00:13:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/22 19:12:39 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_get_index(char *str, char c)
{
	int i;

	i = 0;
	if (!*str)
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0' && c != '\0')
		return (-1);
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2, int code)
{
	int	len1;
	int	len2;
	char	*new_arr;

	if (!*s1)
		return (s2);
	if (!*s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_arr = (char *)malloc(sizeof(char) * (1 + len1 + len2));
	if (!new_arr)
		return (NULL);
	new_arr[len1 + len2] = '\0';
	while(*s1)
		*new_arr++ = *s1++;
	if (code <= 2)
		free(s1 - len1);
	while (*s2)
		*new_arr++ = *s2++;
	if (code >= 2)
		free(s2 - len2);
	return (new_arr - len1 - len2);
}
