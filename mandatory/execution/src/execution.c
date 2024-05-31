/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:59:05 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/31 18:41:44 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_dup_pipes(int fdin, int fdout)
{
	if (fdin != 0)
	{
		dup2(fdin, 0);
		close(fdin);
	}
	if (fdout != 1)
	{
		dup2(fdout, 1);
		close(fdout);
	}
}

int	ft_perror(char *cmd)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": permission denied\n", 2);
	}
	else if (errno == ENOMEM)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": malloc error\n", 2);
	}
	else
		perror(cmd);
	return (errno);
}

void	ft_increment_shellvl(t_shell *shell)
{
	char	*shell_lvl;
	int		shell_lvl_int;

	shell_lvl = ft_getenv("SHLVL", shell->env);
	if (!shell_lvl)
		return ;
	shell_lvl_int = ft_atoi(shell_lvl);
	shell_lvl_int++;
	shell_lvl = ft_itoa(shell_lvl_int);
	if (!shell_lvl)
		return ;
	ft_change_env_value(shell->env, "SHLVL=", shell_lvl);
	free(shell_lvl);
}

char	**ft_list_to_array(t_list *env)
{
	char	**env_array;
	t_list	*tmp;
	int		i;

	i = 0;
	env_array = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!env_array)
		return (NULL);
	while (env)
	{
		tmp = env;
		env_array[i] = ft_strdup(env->content);
		if (!env_array[i])
			return (NULL);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	ft_enable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	ft_execution_process(t_token *token, int fdin, int fdout, t_shell *shell)
{
	char	**env_array;
	char	*cmd_path;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_enable_echoctl();
		if (fdin < 0)
			exit(EXIT_FAILURE);
		ft_dup_pipes(fdin, fdout);
		env_array = ft_list_to_array(shell->env);
		cmd_path = ft_allocate_cmd(token->args, env_array);
		if (!cmd_path)
			return (EXIT_FAILURE);
		execve(cmd_path, token->args, env_array);
		exit(ft_perror(token->args[0]));
	}
	else if (pid < 0)
		return (ft_perror("fork"));
	return (EXIT_SUCCESS);
}

void	sig2_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
	}
	else if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
	}
}

int	ft_exec_function(t_token *token, int fdin, int fdout, t_shell *shell)
{
	char	*last_cmd;

	if (ft_expand(token, shell))
		return (EXIT_FAILURE);
	if (ft_is_builtin(token))
		return (ft_execute_builtin(token, fdout, shell));
	if (ft_strncmp(token->args[0], "./minishell\0", 12) == 0)
		ft_increment_shellvl(shell);
	signal(SIGINT, &sig2_handler);
	signal(SIGQUIT, &sig2_handler);
	if (ft_execution_process(token, fdin, fdout, shell))
		return (EXIT_FAILURE);
	last_cmd = token->args[ft_array_len(token->args) - 1];
	if (ft_change_env_value(shell->env, "_=", last_cmd))
		return (EXIT_FAILURE);
	if (fdin != 0)
		close(fdin);
	if (fdout != 1)
		close(fdout);
	return (0);
}
