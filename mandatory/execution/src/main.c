/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:18:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/03 16:40:03 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_have_builtin(t_cmds *cmds)
{
	if (!ft_strncmp(cmds->cmd[0], "echo", 4))
		return (true);
	else if (!ft_strncmp(cmds->cmd[0], "pwd", 3))
		return (true);
	return (false);
}

void f(void)
{
	system("leaks minishell");
}

void	ft_free_cmds(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds->cmd[i])
	{
		free(cmds->cmd[i]);
		i++;
	}
	free(cmds->cmd);
}

int fun(int ac, char **av, char **env)
{
	// atexit(f);
	t_cmds	cmds;
	cmds.cmd = ft_split(av[1], ' ');
	cmds.infile = NULL;
	cmds.outfile = NULL;
	cmds.fd_in = 0;
	cmds.fd_out = 1;
	ac = 0;
	if (ft_have_builtin(&cmds))
	{
		printf("Calling builtin...\n");
		// ft_echo(&cmds);	workig good √
		// ft_pwd();		workig good √
		//TODO:
		//ft_call_builtin(&cmds);//next func: define which builtin functions
		//call pipex on normal commands
	}
	else
		ft_exec_cmd(cmds.cmd, env, cmds.fd_in, cmds.pipe);//hadi dial command whda
	ft_free_cmds(&cmds);
	return (0);
}