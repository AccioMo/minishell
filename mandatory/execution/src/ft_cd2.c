/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:24:21 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/07 18:36:24 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_dir_exists(char *path, t_shell *shell)
{
	struct stat	statbuf;

	// if (ft_strncmp(path, "/", 1))
	// 	path = ft_realloc(ft_strjoin(ft_getenv("PWD", shell->env), "/"), path);
	ft_set_env(shell->env, "PWD=", path);
	if (stat(path, &statbuf) != 0)
	{
		if (errno == ENOENT)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (EXIT_FAILURE);
		}
		else
		{
			perror("stat");
			return (EXIT_FAILURE);
		}
	}
	return (!(S_ISDIR(statbuf.st_mode)));
}
