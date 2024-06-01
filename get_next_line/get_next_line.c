/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:42:24 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/01 16:16:33 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	allocate_buffer(char **buffer)
{
	if (!*buffer)
	{
		*buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!*buffer)
			return (0);
		*(*buffer + BUFFER_SIZE) = '\0';
		**buffer = '\0';
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || fd > INT_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	line = NULL;
	if (!allocate_buffer(&buffer))
		return (NULL);
	while (buffer)
	{
		if (ft_read(fd, buffer) < 0)
			return (buffer = NULL);
		line = ft_realloc(line, buffer);
		if (line == NULL)
		{
			free(buffer);
			return (buffer = NULL);
		}
		if (*(line + ft_linelen(line) - 1) == '\n')
			return (line);
	}
	return (line);
}
