/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:16:01 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/12 20:16:58 by zouddach         ###   ########.fr       */
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
		rl_on_new_line();
		rl_redisplay();
		ft_parse(buffer, &shell);
		// ft_execute(shell);
		free(buffer);
	}
	return (0);
}
