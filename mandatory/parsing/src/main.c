/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:16:01 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/04 16:02:08 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int ac, char **av, char **env)
{
	char	*buffer;

	if (ac != 1 || av[1])
	{
		ft_putstr_fd("error: too many arguments\n", 2);
		return (1);
	}
	while (true)
	{
		ft_putstr_fd("minishell-v0.2> ", 1);
		buffer = get_next_line(0);
		ft_parse_line(buffer, env);
		if (!buffer)
			break ;
	}
	// ft_execute();
	return (0);
}
