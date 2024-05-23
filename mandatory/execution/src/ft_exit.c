/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:41:57 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/23 13:42:49 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_exit(t_token *token, t_shell *env)
{
	if (token->args[1])
		fprintf(stderr, "minishell: exit: too many arguments\n");
	else
	{
		ft_free_tree(env->root);
		ft_free(env->env);
		exit(0);
	}
}
