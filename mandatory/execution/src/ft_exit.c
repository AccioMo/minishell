/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:41:57 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/04 00:36:06 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_exit(t_shell *env)
{
	ft_putstr_fd("exit\n", 1);
	ft_free_tree(env->root);
	ft_lstclear(&env->env, free);
	exit(0);
}
