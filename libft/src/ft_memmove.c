/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:13:34 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/03 17:27:25 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (src < dest && (src + n) > dest)
	{
		if (!dest && !src)
			return (NULL);
		while (n-- > 0)
			*((unsigned char *) dest + n) = *((unsigned char *) src + n);
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
