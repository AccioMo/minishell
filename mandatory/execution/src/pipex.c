/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:59:05 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/22 19:13:21 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void	ft_dup_pipes(int fdin, int fdout)
{
	if (fdin != 0)
	{
		dup2(fdin, 0);
		close(fdin);
	}
	if (fdout != 1)
	{
		dup2(fdout, 1);
		close(fdout);
	}
}

static void	ft_perror(char *cmd)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": permission denied\n", 2);
	}
	else
		perror(cmd);
}

void	ft_increment_shellvl(t_shell *shell)
{
	char	*shell_lvl;
	int		shell_lvl_int;

	shell_lvl = ft_getenv("SHLVL", shell->env);
	if (!shell_lvl)
		return ;
	shell_lvl_int = ft_atoi(shell_lvl);
	shell_lvl_int++;
	shell_lvl = ft_itoa(shell_lvl_int);
	if (!shell_lvl)
		return ;
	ft_change_env_value(shell, "SHLVL=", shell_lvl);
	free(shell_lvl);
}

int	ft_exec_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	char	*cmd_path;
	pid_t	pid;

	if (ft_expand(token, shell))
		return (EXIT_FAILURE);
	if (ft_have_builtin(token))
		return (ft_execute_builtin(token, fdout, shell));
	cmd_path = ft_allocate_cmd(token->args, shell->env);
	if (!cmd_path)
		exit(EXIT_FAILURE);
	if (ft_strncmp(token->args[0], "./minishell\0", 12) == 0)
		ft_increment_shellvl(shell);
	pid = fork();
	if (pid == 0)
	{
		if (fdin < 0)
			exit(EXIT_FAILURE);
		ft_dup_pipes(fdin, fdout);
		execve(cmd_path, token->args, shell->env);
		ft_perror(token->args[0]);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("fork");
	free(cmd_path);
	if (ft_change_env_value(shell, "_=", token->args[ft_two_d_len(token->args) - 1]))
			return (EXIT_FAILURE);
	if (fdin != 0)
		close(fdin);
	if (fdout != 1)
		close(fdout);
	return (0);
}
