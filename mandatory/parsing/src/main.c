/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:02:25 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/04 05:30:00 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*ft_create_env(char **env)
{
	t_list	*shell_env;
	t_list	*new;
	char	*env_var;
	int		i;

	i = 0;
	if (!env || !env[0])
		return (NULL);
	env_var = ft_strdup(env[i++]);
	if (!env_var)
		return (NULL);
	shell_env = ft_lstnew(env_var);
	if (!shell_env)
		return (NULL);
	while (env[i])
	{
		env_var = ft_strdup(env[i]);
		new = ft_lstnew(env_var);
		if (!new)
			return (NULL);
		ft_lstadd_back(&shell_env, new);
		i++;
	}
	return (shell_env);
}

void	ft_disable_echoctl(void)
{
	struct termios	new_termios;

	tcgetattr(STDIN_FILENO, &new_termios);
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
		rl_redisplay();
	return ;
}

double	ft_gettimeofday(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000);
}

void	ft_clear(void)
{
	ft_putstr_fd("\033[2J", 1);
	ft_putstr_fd("\033[H", 1);
}

static void	ft_minishell(t_shell *shell)
{
	char	*buffer;

	while (TRUE)
	{
		ft_disable_echoctl();
		signal(SIGQUIT, &sig_handler);
		signal(SIGINT, &sig_handler);
		buffer = readline("\033[1m● minishell-v0.7 ❯ \033[0m");
		if (!buffer)
			return ;
		add_history(buffer);
		ft_parse(buffer, shell);
		free(buffer);
		shell->exit_code = ft_priority_token(shell->root, 0, 1, shell);
		rl_on_new_line();
		shell->root = NULL;
	}
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
	ft_clear();
	tcgetattr(STDIN_FILENO, &shell.term);
	signal(g_signal, sig_assign);
	shell.root = NULL;
	shell.exit_code = 0;
	shell.env = ft_create_env(env);
	ft_minishell(&shell);
	ft_lstclear(&shell.env, free);
	ft_free_tree(shell.root);
	tcsetattr(STDIN_FILENO, TCSANOW, &shell.term);
	return (0);
}
