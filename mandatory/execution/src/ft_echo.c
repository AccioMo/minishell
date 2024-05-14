/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:11:30 by zouddach          #+#    #+#             */
/*   Updated: 2024/04/16 12:47:34 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_flag(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-' && cmd[i + 1] == 'n' && !cmd[i + 2])
		return (1);
	return (0);
}

int	ft_echo(t_cmds	*cmds)//-n kat7yd \n
{
	int	i;

	i = 2;
	if (!ft_has_flag(cmds->cmd[1]))
		i = 1;
	while (cmds->cmd[i])
	{
		ft_putstr_fd(cmds->cmd[i], 1);
		if (cmds->cmd[i + 1] && cmds->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!ft_has_flag(cmds->cmd[1]))
		ft_putstr_fd("\n", 1);
	return (0);
}