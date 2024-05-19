/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:03:49 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/18 10:03:30 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_redir_in_function(t_token *token, t_shell *shell)
{
	int	fd;

	fd = open(token->args[0], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

int	ft_redir_out_function(t_token *token, t_shell *shell)
{
	int	fd;

	fd = open(token->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

int	ft_redir_append_function(t_token *token, t_shell *shell)
{
	int	fd;

	fd = open(token->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

int	ft_redir_heredoc_function(t_token *token, t_shell *shell)
{
	int	fd;

	printf("close with: %s\n", token->args[0]);
	// fd = open(token->args[0], O_RDONLY);
	// if (fd < 0)
	// {
	// 	perror("open");
	// 	return (-1);
	// }
	return (0);
}