/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:54:49 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/26 16:00:23 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**ft_get_paths(char **env)
{
	if (!*env)
		return (ft_split("/goinfre/mzeggaf/.brew/bin:/usr/local/bin:\
		/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:\
		/goinfre/mzeggaf/.brew/bin:/Users/mzeggaf/Desktop/nodejs/bin", ':'));
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH", 4))
			return (ft_split((*env) + 5, ':'));
		env++;
	}
	return (NULL);
}

char	*ft_cmd_cpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (*src == '\\' && *(src + 1))
			src++;
		else if (*src == '\'' || *src == '\"')
		{
			src++;
			if (*(src - 1) == '\'')
				while (*src && *src != '\'')
					*(dst + i++) = *src++;
			else if (*(src - 1) == '\"')
				while (*src && *src != '\"')
					*(dst + i++) = *src++;
		}
		else
			*(dst + i++) = *src++;
	}
	*(dst + i) = '\0';
	return (dst);
}

char	*ft_match_path(char *command, char **paths_env)
{
	char	*command_path;
	char	*tmp_path;

	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
		return (perror(command), NULL);
	}
	while (*paths_env)
	{
		tmp_path = ft_strjoin(*paths_env, "/");
		command_path = ft_strjoin(tmp_path, command);
		free(tmp_path);
		if (!command_path)
			return (NULL);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
		paths_env++;
	}
	return (ft_strdup(""));
}
