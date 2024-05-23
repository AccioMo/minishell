/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 00:13:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/23 13:48:32 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_get_index(char *str, char c)
{
	int	i;

	i = 0;
	if (!*str)
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0' && c != '\0')
		return (-1);
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2, int code)
{
	int		len1;
	int		len2;
	char	*new_arr;

	if (!*s1)
		return (s2);
	if (!*s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_arr = (char *)malloc(sizeof(char) * (1 + len1 + len2));
	if (!new_arr)
		return (NULL);
	new_arr[len1 + len2] = '\0';
	while (*s1)
		*new_arr++ = *s1++;
	if (code <= 2)
		free(s1 - len1);
	while (*s2)
		*new_arr++ = *s2++;
	if (code >= 2)
		free(s2 - len2);
	return (new_arr - len1 - len2);
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

char	**ft_get_paths(char **env)
{
	if (!*env)
		return (ft_split("/goinfre/zouddach/.brew/bin:/usr/local/bin:\
		/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:\
		/goinfre/zouddach/.brew/bin:/Users/zouddach/Desktop/nodejs/bin", ':'));
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH", 4))
			return (ft_split((*env) + 5, ':'));
		env++;
	}
	return (NULL);
}

char	*ft_allocate_cmd(char **cmd, char **env)
{
	char	**paths_env;
	char	*cmd_path;

	paths_env = ft_get_paths(env);
	if (!paths_env)
	{
		ft_free(cmd);
		return (NULL);
	}
	cmd_path = ft_match_path(*cmd, paths_env);
	ft_free(paths_env);
	if (!cmd_path)
	{
		ft_free(cmd);
		return (NULL);
	}
	return (cmd_path);
}
