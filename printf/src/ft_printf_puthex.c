/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_puthex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:16:22 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/21 10:46:13 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex_recursive(char c, unsigned int nbr, int *chars_printed)
{
	char	*hexcapital;
	char	*hex;

	hexcapital = "0123456789ABCDEF";
	hex = "0123456789abcdef";
	if (nbr >= 16)
		ft_puthex_recursive(c, nbr / 16, chars_printed);
	if (c == 'X')
		*chars_printed += ft_printf_putchar(hexcapital[nbr % 16]);
	else if (c == 'x')
		*chars_printed += ft_printf_putchar(hex[nbr % 16]);
}

int	ft_printf_puthex(char c, unsigned int nbr)
{
	int	chars_printed;

	chars_printed = 0;
	ft_puthex_recursive(c, nbr, &chars_printed);
	return (chars_printed);
}
