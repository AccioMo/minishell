/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 01:12:11 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/21 10:46:26 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbrrecursive(int nb, int *len)
{
	if (nb == 0)
		*len += ft_printf_putchar('0');
	else if (nb == 2147483647)
		*len += ft_printf_putstr("2147483647");
	else if (nb == -2147483648)
		*len += ft_printf_putstr("-2147483648");
	else if (nb < 0)
	{
		*len += ft_printf_putchar('-');
		ft_putnbrrecursive(-nb, len);
	}
	else
	{
		if (nb >= 10)
		{
			ft_putnbrrecursive((nb / 10), len);
			nb = nb % 10;
		}
		*len += ft_printf_putchar(nb + '0');
	}
}

int	ft_printf_nbr(int nb)
{
	int	chars_printed;

	chars_printed = 0;
	ft_putnbrrecursive(nb, &chars_printed);
	return (chars_printed);
}
