/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:15:59 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/16 16:42:46 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digits(int n)
{
	int	digits;

	digits = 1;
	while (n / 10)
	{
		digits *= 10;
		n /= 10;
	}
	return (digits);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	cnbr;
	int		digits;
	int		sign;

	sign = 1;
	if (fd < 0)
		return ;
	if (n < 0)
	{
		sign = -sign;
		write(fd, "-", 1);
	}
	digits = get_digits(n);
	while (digits)
	{
		cnbr = sign * (n / digits) + 48;
		write(fd, &cnbr, 1);
		n %= digits;
		digits /= 10;
	}
}
