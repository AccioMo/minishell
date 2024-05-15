/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:59:05 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/15 20:59:24 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipex(char **cmds, char **env)
{
	int		end[2];
	int		fdin;

	while (*(cmds + 2))
	{
		fdin = ft_redirect_input(cmds.infile);
		if (pipe(end) < 0)
		{
			close(fdin);
			perror("pipe");
			return (EXIT_FAILURE);
		}
		ft_exec_cmd(*cmds, env, fdin, end);
		close(fdin);
		fdin = dup(end[0]);
		close(end[0]);
		close(end[1]);
		if (fdin < 0)
		{
			perror("dup");
			return (EXIT_FAILURE);
		}
		ft_redirect_output(cmds, fdin, env);
		token = token->next;
	}
	return ();
}