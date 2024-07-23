/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:44:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/23 02:30:44 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution_bonus.h"

int	ft_pwd(int fdout, t_shell *shell)
{
	char	pwd[PATH_MAX];
	char	*path;

	if (!getcwd(pwd, PATH_MAX))
	{
		path = ft_getenv("PWD", shell->env);
		if (path)
		{
			ft_putendl_fd(path, fdout);
			return (EXIT_SUCCESS);
		}
		ft_putstr_fd("minishell: pwd: ERROR retrieving \
current directory: getcwd: cannot access parent \
directories: No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd, fdout);
	return (EXIT_SUCCESS);
}
