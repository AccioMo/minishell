/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:29:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/19 02:42:55 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse(char **env)
{
	char	*buffer;
	char	*user;
	int		fd[2];

	while (true)
	{
		user = ft_strjoin(getenv("USER"), " > ");
		ft_putstr_fd("> ", 1);
		buffer = get_next_line(0);
		if (!buffer)
			break ;
	}
}
