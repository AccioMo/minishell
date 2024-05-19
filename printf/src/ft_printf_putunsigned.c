/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putunsigned.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:03:35 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/21 10:46:06 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putunsignedrecursive(unsigned int nb, int *len)
{
	unsigned int	mx;

	mx = 4294967295;
	if (nb == 0 || nb == -0)
		*len += ft_printf_putchar('0');
	else if (nb == mx)
		*len += ft_printf_putstr("4294967295");
	else
	{
		if (nb >= 10)
		{
			ft_putunsignedrecursive((nb / 10), len);
			nb = nb % 10;
		}
		*len += ft_printf_putchar(nb + '0');
	}
}

int	ft_printf_putunsigned(unsigned int n)
{
	int	chars_printed;

	chars_printed = 0;
	ft_putunsignedrecursive(n, &chars_printed);
	return (chars_printed);
}
