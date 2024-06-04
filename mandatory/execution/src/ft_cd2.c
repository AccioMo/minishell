/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:24:21 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/04 06:16:01 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_dir_exists(char *path, t_shell *shell)
{
	struct stat	statbuf;

	ft_set_env(shell->env, "PWD=", path);
	if (stat(path, &statbuf) != 0)
	{
		if (errno == ENOENT)
		{
			ft_putstr_fd("minishell: cd: ", STDERR);
			ft_putstr_fd(path, STDERR);
			ft_putstr_fd(": No such file or directory\n", STDERR);
			free(path);
			return (EXIT_FAILURE);
		}
		else
		{
			perror("stat");
			free(path);
			return (EXIT_FAILURE);
		}
	}
	return (!(S_ISDIR(statbuf.st_mode)));
}
