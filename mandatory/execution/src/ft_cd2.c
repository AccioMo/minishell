/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:24:21 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/08 16:29:21 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// int	ft_dir_exists(char *path, t_shell *shell)
// {
// 	struct stat	statbuf;

// 	if (path[ft_strlen(path) - 1] != '/')
// 		path = ft_realloc(ft_strjoin(ft_getenv("PWD", shell->env), "/"), path);
// 	if (stat(path, &statbuf) != 0)
// 	{
// 		ft_putstr_fd("minishell: cd: error retrieving current directory: getcwd: \
// 			cannot access parent directories: No such file or directory\n", 2);
// 		ft_set_env(shell->env, "PWD", path);
// 		return (EXIT_FAILURE);
// 	}
// 	return (!(S_ISDIR(statbuf.st_mode)));
// }
