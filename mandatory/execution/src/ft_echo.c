/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:11:30 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/14 23:04:20 by zouddach         ###   ########.fr       */
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

int	ft_echo(t_token	*token)
{
	int	i;

	i = 2;
	if (!ft_has_flag(token->args[1]))
		i = 1;
	while (token->args[i])
	{
		ft_putstr_fd(token->args[i], 1);
		if (token->args[i + 1] && token->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!ft_has_flag(token->args[1]))
		ft_putstr_fd("\n", 1);
	return (0);
}