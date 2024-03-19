/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 01:00:58 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/12 15:34:43 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start < s_len && s_len - start < len)
		len = s_len - start;
	len *= s_len > start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	substr[len] = '\0';
	while (start-- && *s)
		s++;
	ft_strlcpy(substr, s, len + 1);
	return (substr);
}
