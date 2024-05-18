/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:31:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/18 10:36:56 by zouddach         ###   ########.fr       */
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
	if (!env)
		return (NULL);
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

void f()
{
	system("leaks minishell");
}

void sig_handler(int signal)
{
	if (signal == SIGINT)//ctrl^C
		return ;
	if (signal == SIGQUIT)//ctrl^"\"
		printf("wamalk azbi\n");
	
}

void ft_simulate(char *buffer, t_shell *shell)
{
	while (TRUE)
	{
		buffer = readline("minishell-v0.14> ");
		if (!buffer)
		{
			printf("exit\n");
			exit(1);
		}
		add_history(buffer);
		ft_parse(buffer, shell);
		free(buffer);
		// ft_print_tree(shell.root);
		ft_define_priority(shell->root, 0, 1, shell);
		rl_on_new_line();
		while (wait(NULL) > 0)
			wait(NULL);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*buffer;
	t_shell	shell;

	// atexit(f);
	if (ac != 1 || av[1])
	{
		ft_putstr_fd("error: too many arguments\n", 2);
		return (1);
	}
	shell.env = copy_env(env);
	if (!shell.env)
		return (ft_error());
	ft_simulate(buffer, &shell);
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	return (0);
}
