/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:59:05 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/16 08:21:17 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_word_exec(char **cmds, char **env, int infile, int outfile)
{
	pid_t	pid;
	char	*path;

	ft_check_shell_lvl(cmds, env);
	path = ft_get_path(cmds[0], env);//ila makanchi l path...
	if (!path)
		return (1);//later
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, cmds, env) == -1)
			return (ft_error(cmds[0], 1));
	}
	else if (pid < 0)
		return (ft_error("fork", 1));
}