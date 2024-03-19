/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 23:04:25 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/03 00:21:40 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*_s1;
	unsigned char	*_s2;

	_s1 = (unsigned char *) s1;
	_s2 = (unsigned char *) s2;
	while (n && *_s1 && *_s2 && (*_s1 == *_s2))
	{
		n--;
		_s1++;
		_s2++;
	}
	return ((*_s1 - *_s2) * (n != 0));
}
