/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:02:25 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/19 18:11:14 by zouddach         ###   ########.fr       */
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

void disable_sigint_echo(struct termios *orig_termios)
{
    struct termios	new_termios;

    tcgetattr(STDIN_FILENO, orig_termios);
    new_termios = *orig_termios;
    new_termios.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void sig_handler(int signal)
{
	struct termios orig_termios;

	if (signal == SIGINT)
	{
		disable_sigint_echo(&orig_termios);
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
		return ;
	}
	if (signal == SIGQUIT)
		return ;
}

static void ft_simulate(t_shell *shell)
{
	char *buffer;

	while (TRUE)
	{
		buffer = readline("minishell-v0.14> ");
		if (!buffer)
			return ;
		add_history(buffer);
		ft_parse(buffer, shell);
		free(buffer);
		// ft_print_tree(shell.root);
		shell->exit_code = ft_define_priority(shell->root, 0, 1, shell);
		rl_on_new_line();
		while (wait(NULL) > 0)
			wait(NULL);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	if (ac != 1 || av[1])
	{
		ft_putstr_fd("error: too many arguments\n", 2);
		return (1);
	}
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	shell.env = copy_env(env);
	shell.exit_code = 0;
	if (!shell.env)
		return (ft_error());
	ft_simulate(&shell);
	ft_free_tree(shell.root);
	return (0);
}
