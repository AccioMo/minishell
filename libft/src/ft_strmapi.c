/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:15:59 by mzeggaf           #+#    #+#             */
/*   Updated: 2023/11/12 01:39:18 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*cpy;

	if (!s || !f)
		return (NULL);
	i = 0;
	cpy = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	while (*s)
	{
		cpy[i] = f(i, *s);
		s++;
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
