/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 06:08:20 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/12 15:38:43 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;

	if (!s1 || !set)
		return (NULL);
	len = 0;
	while (ft_strchr(set, *s1) && *s1)
		s1++;
	while (*(s1 + len))
		len++;
	while (*s1 && ft_strchr(set, *(s1 + len - 1)) && len)
		len--;
	return (ft_substr(s1, 0, len));
}
