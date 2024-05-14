/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:41:57 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/18 18:41:36 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_cmds *cmds, t_env *env)
{
	if (cmds->cmd[1])
		fprintf(stderr, "minishell: exit: too many arguments\n");
	else
	{
		ft_free_cmds(cmds);
		ft_free_env(env);
		//rl_clear_history();
		//TODO: all what is in there to free needs to be freed here
		exit(0);
	}
}