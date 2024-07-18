/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:02:05 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/18 10:32:59 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void	ft_free(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	*ft_getenv(char *name, t_list *env)
{
	int	i;

	i = 0;
	name = ft_strjoin(name, "=");
	if (!name)
		return (NULL);
	while (env)
	{
		if (!ft_strncmp(env->content, name, ft_strlen(name)))
		{
			free(name);
			return (ft_strchr(env->content, '=') + 1);
		}
		env = env->next;
	}
	free(name);
	return (NULL);
}

int	ft_array_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

char	*ft_realloc(char *line, char *buffer)
{
	char	*str;

	if (buffer == NULL)
		return (line);
	if (line == NULL)
		return (ft_strdup(buffer));
	str = ft_strjoin(line, buffer);
	free(line);
	if (!str)
		return (NULL);
	return (str);
}
