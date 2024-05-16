/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:16:01 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/16 20:31:18 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_error(void)
{
	ft_putstr_fd("error: Malloc failed\n", 2);
	return (1);
}

char	**copy_env(char **env)
{
	int		i;
	char	**shellenv;

	i = 0;
	while (env[i])
		i++;
	shellenv = (char **)malloc(sizeof(char *) * (i + 1));
	if (!shellenv)
		return (NULL);
	i = 0;
	while (env[i])
	{
		shellenv[i] = ft_strdup(env[i]);
		if (!shellenv[i])
		{
			while (i-- >= 0)
				free(shellenv[i]);
			free(shellenv);
			return (NULL);
		}
		i++;
	}
	shellenv[i] = NULL;
	return (shellenv);
}

int	main(int ac, char **av, char **env)
{
	char	*buffer;
	t_shell	shell;

	if (ac != 1 || av[1])
	{
		ft_putstr_fd("error: too many arguments\n", 2);
		return (1);
	}
	shell.env = copy_env(env);
	if (!shell.env)
		return (ft_error());
	while (TRUE)
	{
		buffer = readline("minishell-v0.14> ");
		if (!buffer || !*buffer)
			continue ;
		add_history(buffer);
		ft_parse(buffer, &shell);
		free(buffer);
		ft_print_tree(shell.root);
		stage_one_function(shell.root, 0, 1, &shell);
		rl_on_new_line();
		while (wait(NULL) > 0)
			wait(NULL);
	}
	return (0);
}
