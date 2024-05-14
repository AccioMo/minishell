/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:41:57 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/14 22:58:56 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_token *token, t_shell *env)
{
	if (token->args[1])
		fprintf(stderr, "minishell: exit: too many arguments\n");
	else
	{
		ft_free_token(token);
		ft_free_env(env);
		//rl_clear_history();
		//TODO: all what is in there to free needs to be freed here
		exit(0);
	}
}