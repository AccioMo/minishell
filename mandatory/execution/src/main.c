/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:18:22 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/12 20:29:35 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_print_shellMain(char **r)// needs to be deleted, now its just for debug purposes
{
	int	i;

	i = 0;
	while (r[i])
	{
		ft_putstr_fd(r[i], STDOUT);
		ft_putchar_fd('\n', STDOUT);
		i++;
	}
	return (SUCCESS);
}

int	ft_have_builtin(t_token *token)
{
	if (ft_strncmp(token->args[0], "echo", 4) == 0)//ready    √
		return (TRUE);
	if (ft_strncmp(token->args[0], "pwd", 3) == 0)//ready     √
		return (TRUE);
	if (ft_strncmp(token->args[0], "cd", 2) == 0)//ready      √
		return (TRUE);
	if (ft_strncmp(token->args[0], "unset", 5) == 0)//ready   √
		return (TRUE);
	if (ft_strncmp(token->args[0], "export", 6) == 0)//ready  √
		return (TRUE);
	return (FALSE);
}

void f(void)
{
	system("leaks minishell");
}

void	ft_free_cmds(t_token *token)
{
	int	i;

	i = 0;
	while (token->args && token->args[i])
	{
		free(token->args[i]);
		i++;
	}
	free(token->args);
}

void	ft_free_env(t_shell *env)
{
	int	i;

	i = 0;
	while (env->env && env->env[i])
	{
		free(env->env[i]);
		i++;
	}
	free(env->env);
}

char	**copy_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i-- >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

// int main(int ac, char **av, char **env)
// {
// 	atexit(f);
// 	t_token	cmds;
// 	t_shell	envi;

// 	envi.env = copy_env(env);
// 	cmds.cmd = ft_split(av[1], ' ');
// 	for (int i = 0; cmds.cmd[i]; i++)
// 	{
// 		printf("cmds.cmd[%d] = %s\n", i, cmds.cmd[i]);
// 	}
// 	envi.vars = NULL;
// 	ac = 0;
// 	ft_execute(&cmds, &envi);
// 	ft_free_cmds(&cmds);
// 	ft_free_env(&envi);
// 	// ft_print_shellMain(envi.env);
// 	return (0);
// }

//khass nhandli shellvl