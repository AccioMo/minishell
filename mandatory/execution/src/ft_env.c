/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:20:17 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/30 21:25:21 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_env(t_list *env, int fdout)
{
	int	i;

	i = 0;
	if (!env)
		return (EXIT_SUCCESS);
	while (env)
	{
		ft_putstr_fd(env->content, fdout);
		ft_putchar_fd('\n', fdout);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
