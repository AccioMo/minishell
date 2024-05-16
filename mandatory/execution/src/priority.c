/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:16:19 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/15 21:19:53 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ft_or_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!ft_define_priority(token->left, fdin, fdout, shell))
		return (ft_define_priority(token->right, fdin, fdout, shell));
	return (0);
}

int	ft_and_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (stage_two_function(token->left, fdin, fdout, shell))
		return (stage_one_function(token->right, fdin, fdout, shell));
	return (0);
}