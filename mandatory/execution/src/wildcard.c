/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:36:54 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/04 00:12:57 by mzeggaf          ###   ########.fr       */
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

int	ft_widcard_match(char *pattern, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!pattern || !str)
		return (0);
	while (pattern[i])
	{
		if (pattern[i] == '\"')
			i += ft_index(&pattern[i + 1], '\"') + 1;
		else if (pattern[i] == '\'')
			i += ft_index(&pattern[i + 1], '\'') + 1;
		else if (pattern[i] == '*')
		{
			while (pattern[i] == '*')
				i++;
			while (str[j] && str[j] != pattern[i])
				j++;
		}
		else if (pattern[i] != str[j])
			return (0);
		else
			i++;
	}
	return (1);
}

int	ft_handle_wildecard(t_token *token, char *pattern)
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
		if (ft_widcard_match(pattern, dir_entry->d_name) == 1)
		{
			token->args = ft_append_to_array(token->args, dir_entry->d_name);
			len++;
		}
		dir_entry = readdir(dir);
	}
	closedir(dir);
	return (len);
}

int	ft_found_token(char *str, char c)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '\"')
			j += ft_index(&str[j + 1], '\"') + 1;
		else if (str[j] == '\'')
			j += ft_index(&str[j + 1], '\'') + 1;
		else if (str[j] == c)
			return (1);
		else
			j++;
	}
	return (0);
}

int	ft_wildcard(t_token *token, int i)
{
	int	k;

	token->args[i] = ft_remove_quotes(token->args[i]);
	k = ft_handle_wildecard(token, token->args[i]);
	if (k > 0)
	{
		token->args = ft_remove_from_array(token->args, i);
		k--;
	}
	return (k);
}
