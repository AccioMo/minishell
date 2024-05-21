/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilidcard_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:36:54 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/21 07:37:22 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_realoccate_args(char ***args, int i)
{
	char	**old_args;
	char	**args_i;
	char	**new_args;
	int		j;
	int		x;
	int		new_size;

	old_args = copy_env(*args);
	if (!old_args)
		return;
	args_i = ft_split(old_args[i], ' ');
	if (!args_i)
	{
		ft_free(old_args);
		return;
	}
	new_size = ft_two_d_len(old_args);
	x = 0;
	while (args_i[x])
		x++;
	new_size = new_size - 1 + x;
	new_args = malloc(sizeof(char *) * (new_size + 1));
	if (!new_args)
	{
		ft_free(old_args);
		ft_free(args_i);
		return;
	}
	j = 0;
	while (j < i)
	{
		new_args[j] = ft_strdup(old_args[j]);
		if (!new_args[j])
		{
			ft_free(new_args);
			ft_free(old_args);
			ft_free(args_i);
			return;
		}
		j++;
	}
	// Copy split args from args_i hado homa li kant fihom * w expanditha..
	x = 0;
	while (args_i[x])
	{
		new_args[j] = ft_strdup(args_i[x]);
		if (!new_args[j])
		{
			ft_free(new_args);
			ft_free(old_args);
			ft_free(args_i);
			return;
		}
		j++;
		x++;
	}
	// Copy the rest of old args after index i
	i++;  // Skip the current i li kant fih * w expanditha.
	while (old_args[i])
	{
		new_args[j] = ft_strdup(old_args[i]);
		if (!new_args[j])
		{
			ft_free(new_args);
			ft_free(old_args);
			ft_free(args_i);
			return;
		}
		j++;
		i++;
	}
	new_args[j] = NULL;
	ft_free(old_args);
	ft_free(args_i);
	free(*args);
	*args = new_args;
}

void	ft_handle_wildecard(t_token *token, int i)//needs to be an int funtion for malloc return
{
	DIR		*dir;
	struct dirent	*entry;
	char	*dirname;
	char	cwd[255];
	char *tmp;

	entry = NULL;
	dirname = ft_strdup(getcwd(cwd, 255));//hna khasni ndir strjoin l token->args[i] w * ila makantch * 
	if (!dirname)
		return ;//error managing...
	dir = opendir(dirname);
	if (!dir)
	{
		free(dirname);
		return ;
	}
	entry = readdir(dir);
	if (!entry)
	{
		free(dirname);
		closedir(dir);
		return ;
	}
	// ft_printf("Files in %s:\n", dirname);
	tmp = ft_strdup("");
	while (entry)
	{
		if (entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		// ft_printf("%s\n", entry->d_name);
		tmp = ft_strjoin(tmp, entry->d_name);
		if (!tmp)
			return ;//error managing...
		tmp = ft_strjoin(tmp, " ");
		if (!tmp)
			return ;
		entry = readdir(dir);
	}
	// ft_printf("tmp: %s\n", tmp);//khedama daba wa2akhiran. but hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh khas npasiha ka 2d array hhhhhhhh fuck: Update done azbi wakha mokhi kit7r9 db
	free(token->args[i]);
	token->args[i] = tmp;
	closedir(dir);
}