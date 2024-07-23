/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:11:30 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/23 02:30:44 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"

static int	ft_ignore_flag(char *name, int c)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (name[i] != c)
			return (0);
		i++;
	}
	return (1);
}

static int	ft_has_flag(char **args)
{
	int	j;
	int	c;

	j = 1;
	c = 0;
	while (args[j])
	{
		if (args[j][0] == '-' && args[j][1] == 'n')
		{
			if (ft_ignore_flag(&args[j][1], 'n'))
				c++;
			else
				break ;
		}
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
