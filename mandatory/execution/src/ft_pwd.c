/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:44:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/22 20:27:51 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_pwd(int fdout, char **env)
{
	char *l;

	l = ft_getenv("PWD", env);
	if (!*l)
	{
		ft_putstr_fd("minishell: pwd: ERROR retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(l, fdout);//cmd->outfile
	ft_putstr_fd("\n", fdout);//cmd->outfile
	return (0);
}
