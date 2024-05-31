/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:16:19 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/30 17:54:49 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_or_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (ft_priority_token(token->left, fdin, fdout, shell))
		return (ft_priority_token(token->right, fdin, fdout, shell));
	return (0);
}

int	ft_and_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	if (!ft_priority_token(token->left, fdin, fdout, shell))
		return (ft_priority_token(token->right, fdin, fdout, shell));
	return (0);
}
