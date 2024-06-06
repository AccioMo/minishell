/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:02:25 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/06 11:25:16 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*ft_create_env(char **env)
{
	t_list	*shell_env;
	t_list	*new;
	char	pwd[PATH_MAX];
	char	*env_var;
	int		i;

	i = 0;
	getcwd(pwd, PATH_MAX);
	if (!env || !env[0])
	{
		shell_env = ft_lstnew(ft_strdup("SHLVL=1"));
		env_var = ft_strjoin("PWD=", pwd);
		if (!env_var)
			return (NULL);
		ft_lstadd_back(&shell_env, ft_lstnew(env_var));
		if (!shell_env)
			return (NULL);
		return (shell_env);
	}
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

	ft_clear();
	while (TRUE)
	{
		ft_disable_echoctl();
		signal(SIGINT, &sig_handler);
		signal(SIGQUIT, &sig_handler);
		if (shell->exit_code == 0)
			buffer = ft_strjoin("\033[1;32m●\033[0m\033[1m minish-v1.0 ", \
			getenv("USER"));
		else
			buffer = ft_strjoin("\033[1;31m●\033[0m\033[1m minish-v1.0 ", \
			getenv("USER"));
		buffer = ft_realloc(buffer, " ❯ \033[0m");
		buffer = readline(buffer);
		if (!buffer)
			return (ft_exit(shell));
		add_history(buffer);
		ft_parse(buffer, shell);
		free(buffer);
		shell->exit_code = ft_priority_token(shell->root, 0, 1, shell);
		rl_on_new_line();
		shell->root = NULL;
	}
}

void	ft_non_interactive(t_shell *shell)
{
	char	*buffer;

	buffer = readline(NULL);
	if (!buffer)
		ft_exit(shell);
	ft_parse(buffer, shell);
	shell->exit_code = ft_priority_token(shell->root, 0, 1, shell);
	shell->root = NULL;
	free(buffer);
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
	return (0);
}
