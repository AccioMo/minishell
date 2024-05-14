/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:44:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/12 19:58:57 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_pwd(t_shell *env)
{
	char	*pwd;

	pwd = ft_getenv("PWD", env->env);
	if (!pwd)
	{
		ft_putstr_fd("minishell: pwd: ERROR retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 2);
		return (ERROR);
	}
	ft_putstr_fd(pwd, 1);//cmd->outfile
	ft_putstr_fd("\n", 1);//cmd->outfile
	free(pwd);
	return (0);
}
