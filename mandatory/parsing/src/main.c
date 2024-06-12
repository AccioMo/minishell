/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:02:25 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/12 20:11:25 by mzeggaf          ###   ########.fr       */
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

int	set_exit_code(int exit_code, int set)
{
	static int	code;

	if (set)
		code = exit_code;
	return (code);
}

void	sig_handler(int signal)
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

	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &shell->terminos);
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

void	f(void)
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	if (ac != 1 || av[1])
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		return (1);
	}
	// atexit(f);
	tcgetattr(STDIN_FILENO, &shell.terminos);
	rl_catch_signals = 0;
	shell.heredocs = NULL;
	shell.root = NULL;
	shell.exit_code = 0;
	shell.env = ft_create_env(env);
	if (!shell.env)
		return (ft_perror("minishell"));
	if (isatty(STDIN_FILENO))
		ft_minishell(&shell);
	else
		ft_putstr_fd("minishell: not a tty\n", 2);
	ft_clear_heredocs(shell.heredocs);
	ft_lstclear(&shell.env, free);
	ft_free_tree(shell.root);
	tcsetattr(STDIN_FILENO, TCSANOW, &shell.terminos);
	ft_putstr_fd("exit\n", 1);
	return (shell.exit_code);
}
// echo hello >> =$sdfdsf* >> =$sdsdfsdf* =*
// cat    <| ls
//  echo hi >./test_files/invalid_permission | echo bye
// ls >"./outfiles/outfile with spaces"
// cd /tmp && ls -al >     "hello    world"   && ls -al && cat "hello    world" && rm -fr "hello    world"
// cd /aaaaaaaa && echo $?
// /bin