/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:02:25 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/11 21:20:39 by mzeggaf          ###   ########.fr       */
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
		ft_set_env(shell_env, "PWD", pwd);
		ft_set_env(shell_env, "PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
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

	// ft_clear();
	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &shell->terminos);
		signal(SIGINT, &sig_handler);
		signal(SIGQUIT, &sig_handler);
		char *dir = ft_strnstr(ft_getenv("PWD", shell->env), ft_getenv("HOME", shell->env), -1);
		if (dir)
			dir = ft_strjoin("~", &dir[ft_strlen(getenv("HOME"))]);
		else
			dir = ft_strdup(ft_getenv("PWD", shell->env));
		if (shell->exit_code == 0)
			buffer = ft_strjoin("\033[1;32m●\033[0m\033[1m shv1 ", \
			dir);
		else
			buffer = ft_strjoin("\033[1;31m●\033[0m\033[1m shv1 ", \
			dir);
		free(dir);
		buffer = ft_realloc(buffer, " ❯ \033[0m");
		buffer = readline(buffer);
		if (!buffer)
			return ;
		add_history(buffer);
		if (!ft_parse(buffer, shell))
			ft_priority_token(shell->root, 0, 1, shell);
		if (!shell->root)
			return ;
	}
}

void	ft_non_interactive(t_shell *shell)
{
	char	*buffer;

	buffer = readline("");
	// ft_putstr_fd("\033[A", 1);
	// rl_replace_line("", 0);
	// rl_redisplay();
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
	tcgetattr(STDIN_FILENO, &shell.terminos);
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
	tcsetattr(STDIN_FILENO, TCSANOW, &shell.terminos);
	// ft_putstr_fd("exit\n", 1);
	return (shell.exit_code);
}
// echo hello >> =$sdfdsf* >> =$sdsdfsdf* =*
// cat    <| ls
//  echo hi >./test_files/invalid_permission | echo bye
// ls >"./outfiles/outfile with spaces"
// cd /tmp && ls -al >     "hello    world"   && ls -al && cat "hello    world" && rm -fr "hello    world"
// cd /aaaaaaaa && echo $?
// /bin