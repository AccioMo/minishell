/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:09:37 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/25 20:57:13 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *env[])
{
	int		exit_status;

	ft_input_check(argc, argv);
	if (ft_strncmp(*(argv + 1), "here_doc\0", 9) == 0)
		exit_status = ft_here_doc(argv + 2, env);
	else
		exit_status = ft_pipex(argv + 1, env);
	while (wait(NULL) > 0)
		wait(NULL);
	return (exit_status);
}
