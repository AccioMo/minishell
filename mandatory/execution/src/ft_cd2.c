/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:48:09 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/31 00:02:12 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_dir_exists(t_token *token)
{
    struct stat statbuf;
    if (stat(token->args[1], &statbuf) != 0) {
        // stat() failed, could be due to the directory not existing
        if (errno == ENOENT) {
            ft_putstr_fd("minishell: cd: ", STDERR);
            ft_putstr_fd(token->args[1], STDERR);
            ft_putstr_fd(": No such file or directory\n", STDERR);
            return (EXIT_FAILURE); // Directory does not exist
        } else {
            perror("stat");
            return (EXIT_FAILURE); // Some other error occurred
        }
    }
    return (!(S_ISDIR(statbuf.st_mode)));// Return 1 if it's a directory, 0 otherwise that why zdt ! flwl
}