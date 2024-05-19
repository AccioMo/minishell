/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putadr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 01:32:54 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/21 10:46:21 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printadr_recursive(uintptr_t adr, int *chars_printed)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (adr >= 16)
		ft_printadr_recursive(adr / 16, chars_printed);
	*chars_printed += ft_printf_putchar(hex[adr % 16]);
}

int	ft_printf_putadr(uintptr_t adr)
{
	int	chars_printed;

	chars_printed = 0;
	chars_printed += ft_printf_putstr("0x");
	if (adr)
		ft_printadr_recursive(adr, &chars_printed);
	else
		chars_printed += ft_printf_putchar('0');
	return (chars_printed);
}
