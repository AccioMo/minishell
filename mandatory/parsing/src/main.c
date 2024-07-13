/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:02:25 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/07/13 18:50:23 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_reset_term(void)
{
	static struct termios	term;
	static int				first;

	if (!first)
	{
		tcgetattr(STDIN_FILENO, &term);
		first = 1;
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	main_sig_handler(int signal)
{
	g_signal = signal;
	if (signal == SIGINT)
	{
		set_exit_code(1, true);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		if (waitpid(-1, NULL, WNOHANG) == 0)
			return ;
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
		rl_redisplay();
	return ;
}

static void	ft_minishell(t_shell *shell)
{
	char	*buffer;

	signal(SIGINT, main_sig_handler);
	signal(SIGQUIT, main_sig_handler);
	while (1)
	{
		buffer = readline("minishell$ ");
		if (!buffer)
			return ;
		if (!valid_line(buffer))
			continue ;
		add_history(buffer);
		shell->exit_code = set_exit_code(0, false);
		if (!ft_parse(buffer, shell))
		{
			ft_priority_token(shell->root, 0, 1, shell);
			if (!shell->root)
				return ;
		}
		ft_free_tree(shell->root);
		shell->root = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	if (ac != 1 || av[1])
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		return (1);
	}
	ft_reset_term();
	rl_catch_signals = 0;
	shell.root = NULL;
	shell.exit_code = 0;
	shell.env = ft_init_env(env, &shell);
	ft_increment_shellvl(&shell);
	if (!shell.env)
		return (ft_perror("minishell", errno));
	if (isatty(STDIN_FILENO))
		ft_minishell(&shell);
	else
		ft_putstr_fd("minishell: not a tty\n", 2);
	ft_lstclear(&shell.env, free);
	ft_free_tree(shell.root);
	ft_reset_term();
	ft_putstr_fd("exit\n", 1);
	return (shell.exit_code);
}
