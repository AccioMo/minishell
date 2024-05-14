/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:16:01 by mzeggaf           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/13 20:21:50 by mzeggaf          ###   ########.fr       */
=======
/*   Updated: 2024/05/12 20:16:58 by zouddach         ###   ########.fr       */
>>>>>>> 8a554550f451b3066b68d712fc39fdf1a2b0b976
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
	while (TRUE)
	{
		buffer = readline("minishell-v0.14> ");
		if (!buffer || !*buffer)
			continue ;
		add_history(buffer);
		ft_parse(buffer, &shell);
		// ft_execute(shell);
		free(buffer);
		// ft_print_tree(shell.root);
		stage_one_function(shell.root, 0, 1, &shell);
		rl_on_new_line();
		while (wait(NULL) > 0)
			wait(NULL);
	}
	return (0);
}
