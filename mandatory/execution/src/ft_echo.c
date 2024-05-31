/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:11:30 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/31 19:07:49 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_has_flag(char **args)
{
	int	j;
	int	c;

	j = 1;
	c = 0;
	while (args[j])
	{
		if (args[j][0] == '-' && args[j][1] == 'n' && args[j][2] == '\0')
			c++;
		else
			break ;
		j++;
	}
	return (c);
}

int	ft_echo(t_token	*token, int fdout)
{
	int	i;

	i = 2;
	if (!token->args[1])
	{
		ft_putstr_fd("\n", fdout);
		return (EXIT_SUCCESS);
	}
	if (!ft_has_flag(token->args))
		i = 1;
	else
		i = ft_has_flag(token->args) + 1;
	while (token->args && token->args[i])
	{
		ft_putstr_fd(token->args[i], fdout);
		if (token->args[i + 1])
			ft_putstr_fd(" ", fdout);
		i++;
	}
	if (!ft_has_flag(token->args))
		ft_putstr_fd("\n", fdout);
	return (0);
}
