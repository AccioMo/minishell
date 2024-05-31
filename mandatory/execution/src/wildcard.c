/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:36:54 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/30 18:16:06 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**ft_remove_from_array(char **array, int x)
{
	char	**new_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!array)
		return (NULL);
	while (array[i])
		i++;
	new_array = (char **)malloc(sizeof(char *) * i);
	if (!new_array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		if (i == x)
			free(array[i++]);
		else
			new_array[j++] = array[i++];
	}
	new_array[j] = NULL;
	free(array);
	return (new_array);
}

char	**ft_append_to_array(char **args, char *new_arg)
{
	char	**new_args;
	int		i;

	i = 0;
	while (args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = ft_strdup(new_arg);
	if (!new_args[i])
	{
		ft_free(new_args);
		return (NULL);
	}
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}

static int	ft_handle_wildecard(t_token *token)
{
	struct dirent	*dir_entry;
	char			cwd[PATH_MAX];
	DIR				*dir;
	int				len;

	len = 0;
	getcwd(cwd, sizeof(cwd));
	dir = opendir(cwd);
	if (!dir)
		return (1);
	dir_entry = readdir(dir);
	while (dir_entry)
	{
		if (!ft_strncmp(dir_entry->d_name, ".\0", 2) || \
			!ft_strncmp(dir_entry->d_name, "..\0", 3))
		{
			dir_entry = readdir(dir);
			continue ;
		}
		token->args = ft_append_to_array(token->args, dir_entry->d_name);
		dir_entry = readdir(dir);
		len++;
	}
	closedir(dir);
	return (len);
}

int	ft_wildcard(t_token *token)
{
	int	wildcard;
	int	i;

	i = 0;
	wildcard = 0;
	while (token->args[i])
	{
		if (!ft_strncmp(token->args[i], "*\0", 2))
		{
			wildcard++;
			token->args = ft_remove_from_array(token->args, i);
			i += ft_handle_wildecard(token);
		}
		else if (!ft_strncmp(token->args[i], "\"*\"\0", 4) \
				|| !ft_strncmp(token->args[i], "\'*\'\0", 4))
			token->args[i] = ft_remove_quotes(token->args[i]);
		else
			i++;
	}
	return (wildcard);
}
