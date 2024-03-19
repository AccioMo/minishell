/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:16:01 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/19 02:44:17 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	if (ac != 1 || av[1])
	{
		ft_putstr_fd("Error: too many arguments\n", 2);
		return (1);
	}
	ft_parse(env);
	// ft_execute();
	return (0);
}
