/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:02:47 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/30 20:24:41 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_print_shell(t_list *env, int fdout)
{
	int	i;
	int	j;

	i = 0;
	while (env)
	{
		j = 0;
		ft_putstr_fd("declare -x ", fdout);
		while (env->content[j] && env->content[j] != '=')
			ft_putchar_fd(env->content[j++], fdout);
		if (env->content[j] == '=')
		{
			ft_putchar_fd('=', fdout);
			ft_putchar_fd('\'', fdout);
			j++;
		}
		while (env->content[j])
			ft_putchar_fd(env->content[j++], fdout);
		ft_putchar_fd('\'', fdout);
		ft_putchar_fd('\n', fdout);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_change_var(char **var)
{
	int		i;
	int		j;
	char	*new_var;

	i = 0;
	j = 0;
	new_var = (char *)malloc(sizeof(char) * (ft_strlen(*var) + 3));
	if (!new_var)
		return (EXIT_FAILURE);
	while ((*var)[i] && (*var)[i] != '=')
		new_var[j++] = (*var)[i++];
	new_var[j++] = '=';
	new_var[j++] = '"';
	while ((*var)[i])
		new_var[j++] = (*var)[i++];
	new_var[j++] = '"';
	new_var[j] = '\0';
	free(*var);
	*var = new_var;
	return (EXIT_SUCCESS);
}

// char	**ft_realloc_env(t_list *env, int size, char *new_var)
// {
// 	char	**new_env;
// 	int		i;

// 	i = 0;
// 	if (ft_count_char(new_var, '=') > 1)
// 		ft_change_var(&new_var);
// 	new_env = (char **)malloc(sizeof(char *) * (size + 1));
// 	if (!new_env)
// 		return (NULL);
// 	while (env[i])
// 	{
// 		new_env[i] = ft_strdup(env[i]);
// 		if (!new_env[i])
// 		{
// 			ft_free(new_env);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	new_env[i] = ft_strdup(new_var);
// 	if (!new_env[i])
// 		return (ft_free(new_env), NULL);
// 	new_env[i + 1] = NULL;
// 	ft_free(env);
// 	return (new_env);
// }

int	ft_export_lines_saver(char *new_var, t_list *env)
{
	t_list	*head;

	head = env;
	if (ft_strncmp(new_var, "_\0", 2))
		if (ft_change_env_value(env, "_=", "export"))
			return (EXIT_FAILURE);
	while (env)
	{
		if (!ft_strncmp(env->content, new_var, ft_strlen(new_var)))
		{
			free(env->content);
			env->content = ft_strdup(new_var);
			if (!env->content)
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		env = env->next;
	}
	ft_lstadd_back(&head, ft_lstnew(new_var));
	return (EXIT_SUCCESS);
}

int	ft_export(t_token *token, t_shell *shell, int fdout)
{
	int	j;

	j = 0;
	if (ft_array_len(token->args) == 1)
		return (ft_print_shell(shell->env, fdout));
	while (token->args[++j])
	{
		if (ft_strchr(token->args[j], '=') == NULL)
			token->args[j] = ft_strjoin_free(token->args[j], "=", 0);
		if (ft_var_exist(shell, token->args[j]))
			continue ;
		if (ft_isalpha(token->args[j][0]) == 0)
		{
			ft_putstr_fd("export: `", fdout);
			ft_putstr_fd(token->args[1], fdout);
			ft_putstr_fd("': not a valid identifier\n", fdout);
			return (EXIT_FAILURE);
		}
		if (ft_export_lines_saver(token->args[j], shell->env))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
