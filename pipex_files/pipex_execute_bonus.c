/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 20:32:48 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/26 15:07:54 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_perror(char **cmd)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd(*cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd(*cmd, 2);
		ft_putstr_fd(": permission denied\n", 2);
	}
	else
		perror(*cmd);
}

void	ft_dup_pipes(int cmd_in, int *fd_pipe)
{
	if (dup2(cmd_in, 0) < 0 || dup2(fd_pipe[1], 1) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(cmd_in);
		close(fd_pipe[1]);
		close(fd_pipe[0]);
	}
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

void	ft_exec_cmd(char *full_cmd, char **env, int cmd_in, int *fd_pipe)
{
	char	**cmd;
	char	*cmd_path;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd_in < 0)
			exit(EXIT_FAILURE);
		ft_dup_pipes(cmd_in, fd_pipe);
		cmd = ft_cmd_split(full_cmd, ' ');
		if (!cmd)
			exit(EXIT_FAILURE);
		cmd_path = ft_allocate_cmd(cmd, env);
		if (!cmd_path)
			exit(EXIT_FAILURE);
		execve(cmd_path, cmd, env);
		ft_perror(cmd);
		free(cmd_path);
		ft_free(cmd);
		exit(1);
	}
	else if (pid < 0)
		perror("fork");
}
