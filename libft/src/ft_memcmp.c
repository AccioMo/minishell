/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 01:17:29 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/03 01:03:48 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*_s1;
	unsigned char	*_s2;

	_s1 = (unsigned char *) s1;
	_s2 = (unsigned char *) s2;
	while (n > 1 && (*_s1 == *_s2))
	{
		n--;
		_s1++;
		_s2++;
	}
	return ((*_s1 - *_s2) * (n != 0));
}
