/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:16:19 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/16 21:15:41 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execution.h"

int	ft_or_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!ft_define_priority(token->left, fdin, fdout, shell))
		return (ft_define_priority(token->right, fdin, fdout, shell));
	return (0);
}

int	ft_and_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (ft_check_redirections(token->left, fdin, fdout, shell))
		return (ft_define_priority(token->right, fdin, fdout, shell));
	return (0);
}