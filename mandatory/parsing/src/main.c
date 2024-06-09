/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:02:25 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/09 16:43:34 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_minishell(t_shell *shell)
{
	char	*buffer;

	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &shell->term);
		signal(SIGINT, &sig_handler);
		signal(SIGQUIT, &sig_handler);
		buffer = readline("minishell % ");
		if (!buffer)
			return ;
		add_history(buffer);
		if (!ft_parse(buffer, shell))
			ft_priority_token(shell->root, 0, 1, shell);
	}
}

void	ft_non_interactive(t_shell *shell)
{
	char	*buffer;

	buffer = readline("");
	ft_putstr_fd("\033[A", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	if (!buffer)
		ft_exit(NULL, shell);
	add_history(buffer);
	if (!ft_parse(buffer, shell))
		ft_priority_token(shell->root, 0, 1, shell);
}

void	sig_assign(int signal)
{
	g_signal = signal;
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	if (ac != 1 || av[1])
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		return (1);
	}
	tcgetattr(STDIN_FILENO, &shell.term);
	signal(g_signal, sig_assign);
	shell.root = NULL;
	shell.exit_code = 0;
	shell.env = ft_create_env(env);
	if (!shell.env)
		return (ft_perror("minishell"));
	if (isatty(STDIN_FILENO))
		ft_minishell(&shell);
	else
		ft_non_interactive(&shell);
	ft_lstclear(&shell.env, free);
	ft_free_tree(shell.root);
	tcsetattr(STDIN_FILENO, TCSANOW, &shell.term);
	return (shell.exit_code);
}
