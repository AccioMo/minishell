/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 02:20:53 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/09 19:36:02 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_larger_than(const char *str, char *max)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(max);
	while (*str == '0')
		str++;
	while (*(str + i) >= '0' && *(str + i) <= '9')
		i++;
	while (*str >= '0' && *str <= '9' && i == len)
	{
		if (*str++ > *max++)
			return (0);
	}
	return (i <= len);
}

int	ft_atoi(const char *str)
{
	int		nbr;
	char	sign;

	nbr = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
		{
			sign = -1;
			if (!ft_larger_than(str, "2147483648"))
				return (-1);
		}
		else
			if (!ft_larger_than(str, "2147483647"))
				return (-1);
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0') * sign;
		str++;
	}
	return (nbr);
}
