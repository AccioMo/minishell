/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:16:01 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/09 21:03:14 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	main(int ac, char **av, char **env)
{
	char	*buffer;
	t_shell	shell;

	if (ac != 1 || av[1])
	{
		ft_putstr_fd("error: too many arguments\n", 2);
		return (1);
	}
	shell.env = env;
	shell.vars = NULL;
	while (TRUE)
	{
		buffer = readline("minishell-v0.2> ");
		add_history(buffer);
		ft_parse(buffer, &shell);
		if (!buffer)
			break ;
	}
	// ft_execute();
	return (0);
}
