/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:42:53 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/01/11 20:40:25 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_linelen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (*(str + len))
		len++;
	return (len);
}

int	ft_bufferlen(char *buffer)
{
	int	len;

	len = 0;
	if (!buffer)
		return (0);
	while (*(buffer + len) != '\n' && *(buffer + len) != '\0')
		len++;
	return (len + (*(buffer + len) == '\n'));
}

static char	*ft_strncpy(char *dest, char *src, int n)
{
	while (n > 0 && *src)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	*dest = '\0';
	return (dest);
}

char	*ft_realloc(char *line, char *buffer)
{
	char	*str;
	int		l_line;
	int		l_buffer;

	if (buffer == NULL)
		return (line);
	l_line = ft_linelen(line);
	l_buffer = ft_bufferlen(buffer);
	str = (char *)malloc(sizeof(char) * (l_line + l_buffer + 1));
	if (!str)
		return (free(line), NULL);
	ft_strncpy(ft_strncpy(str, line, l_line), buffer, l_buffer);
	if (line)
		free(line);
	return (str);
}

char	*ft_read(int fd, char *buffer)
{
	int	rd;

	rd = ft_bufferlen(buffer);
	if (*(buffer + rd))
		ft_strncpy(buffer, buffer + rd, ft_linelen(buffer));
	else
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == 0)
		{
			free(buffer);
			return (NULL);
		}
		*(buffer + rd) = '\0';
	}
	return (buffer);
}
