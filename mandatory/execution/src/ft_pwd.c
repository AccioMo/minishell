/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:44:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/18 11:23:34 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_pwd(int fdout)
{
	char	pwd[255];

	getcwd(pwd, 255);
	if (!*pwd)
	{
		ft_putstr_fd("minishell: pwd: ERROR retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(pwd, fdout);//cmd->outfile
	ft_putstr_fd("\n", fdout);//cmd->outfile
	return (0);
}
