/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 21:10:12 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/03 06:36:44 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	while (i && str[i] != (char)c)
		i--;
	if (i == 0 && (char)c != str[i])
		return (NULL);
	return ((char *)str + i);
}
