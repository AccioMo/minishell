/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:02:25 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/30 23:00:09 by mzeggaf          ###   ########.fr       */
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
	if (!env)
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

void	ft_disable_echo(void)
{
	struct termios	new_termios;

	tcgetattr(STDIN_FILENO, &new_termios);
	new_termios.c_lflag = new_termios.c_lflag & ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void	sig_handler(int signal)
{
	pid_t	pid;

	if (signal == SIGINT)
	{
		// rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		pid = waitpid(-1, NULL, WNOHANG);
		if (pid != -1)
			ft_putstr_fd("Quit: 3\n", 1);
		rl_redisplay();
	}
	return ;
}

static void ft_minishell(t_shell *shell)
{
	char *buffer;

	while (TRUE)
	{
		buffer = readline("minishell-v0.47> ");
		if (!buffer)
			return ;
		add_history(buffer);
		ft_parse(buffer, shell);
		free(buffer);
		// ft_print_tree(shell->root);
		shell->exit_code = ft_priority_token(shell->root, 0, 1, shell);
		rl_on_new_line();
		shell->root = NULL;
	}
}

void f()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	if (ac != 1 || av[1])
	{
		ft_putstr_fd("error: too many arguments\n", 2);
		return (1);
	}
	ft_disable_echo();
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	shell.root = NULL;
	shell.exit_code = 0;
	shell.env = ft_create_env(env);
	if (!shell.env)
		return (ft_perror("minishell"));
	ft_minishell(&shell);
	ft_lstclear(&shell.env, free);
	ft_free_tree(shell.root);
	return (0);
}
