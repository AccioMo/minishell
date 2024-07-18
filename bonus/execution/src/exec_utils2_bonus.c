/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 00:13:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/18 11:19:40 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"

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

char	*ft_match_path(char *command, char **paths_env)
{
	char	*command_path;
	char	*tmp_path;

	if (!paths_env || !*paths_env || ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
		return (ft_putstr_fd("minishell: ", 2), perror(command), NULL);
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
	return (ft_perror(command, ENOENT), NULL);
}

char	**ft_get_paths(char **env)
{
	if (!env || !*env)
		return (NULL);
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
	cmd_path = ft_match_path(*cmd, paths_env);
	ft_free(paths_env);
	if (!cmd_path)
	{
		ft_free(cmd);
		return (NULL);
	}
	return (cmd_path);
}

void	ft_close_fds(int fdin, int fdout)
{
	if (fdin != 0)
		close(fdin);
	if (fdout != 1)
		close(fdout);
}
