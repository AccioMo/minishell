/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:15:59 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/12 21:38:04 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_mag(int n)
{
	int	digits;

	digits = 1;
	while (n / 10)
	{
		n /= 10;
		digits += 1;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*nstr;
	int		digits;
	int		sign;

	sign = 1;
	digits = get_mag(n) + (n < 0);
	nstr = (char *)malloc((digits + 1) * sizeof(char));
	if (!nstr)
		return (NULL);
	*nstr = '-';
	if (n < 0)
		sign = -1;
	else
		*nstr = '0';
	nstr += digits;
	*nstr = '\0';
	while (n)
	{
		nstr--;
		*nstr = sign * (n % 10) + 48;
		n /= 10;
		digits--;
	}
	return (nstr - digits);
}
