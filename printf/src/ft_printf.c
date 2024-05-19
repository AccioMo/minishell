/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:54:56 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/21 10:45:50 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_conversions(va_list args, char c)
{
	int	chars_printed;

	chars_printed = 0;
	if (c == '%')
		chars_printed += ft_printf_putchar('%');
	else if (c == 'c' || c == 'C')
		chars_printed += ft_printf_putchar(va_arg(args, int));
	else if (c == 's')
		chars_printed += ft_printf_putstr(va_arg(args, char *));
	else if (c == 'd' || c == 'i' || c == 'D')
		chars_printed += ft_printf_nbr(va_arg(args, int));
	else if (c == 'p')
		chars_printed += ft_printf_putadr(va_arg(args, uintptr_t));
	else if (c == 'x' || c == 'X')
		chars_printed += ft_printf_puthex(c, va_arg(args, unsigned int));
	else if (c == 'u' || c == 'U')
		chars_printed += ft_printf_putunsigned(va_arg(args, unsigned int));
	else
		chars_printed += ft_printf_putchar(c);
	return (chars_printed);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		chars_printed;
	va_list	args;

	i = 0;
	chars_printed = 0;
	if (write(1, "", 0) == -1)
		return (-1);
	va_start(args, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%' && !s[i + 1])
			return (chars_printed);
		else if (s[i] == '%')
		{
			chars_printed += ft_conversions(args, s[i + 1]);
			i++;
		}
		else if (s[i] != '%' && s[i])
			chars_printed += ft_printf_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (chars_printed);
}
// #include <fcntl.h>
// #include <stdio.h>
// int main()
// {
// 	char a;
// 	char b;

// 	fclose(stdout);
// 	a = ft_printf("%d\n", 67) + 50;
// 	b = printf("%d\n", 67) + 50;
// 	int fd = open("file.txt", O_RDWR);
// 	write(fd, &a, 1);
// 	write(fd, &b, 1);
// 	return (0);
// }