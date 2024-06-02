/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:36:54 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/02 17:57:12 by mzeggaf          ###   ########.fr       */
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
	char	*end_pattern;
	char	*start;
	int		end;
	int		wildcard;

	if (!pattern || !str)
		return (0);
	wildcard = ft_index(pattern, '*');
	if (wildcard != 0)
		start = ft_strnstr(str, pattern, wildcard);
	else
		start = str;
	if (ft_strchr(pattern + wildcard + 1, '*'))
		end = ft_widcard_match(pattern + wildcard + 1, start);
	else
	{
		end_pattern = ft_strchr(pattern, '*') + 1;
		end = ft_strnstr(start + ft_strlen(start) - \
			ft_strlen(end_pattern), end_pattern, -1) != NULL;
	}
	if (!start || !end)
		return (0);
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

int	ft_found_wildcard(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '\"')
			j += ft_index(&str[j + 1], '\"') + 1;
		else if (str[j] == '\'')
			j += ft_index(&str[j + 1], '\'') + 1;
		else if (str[j] == '*')
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
		token->args = ft_remove_from_array(token->args, i);
	i += k;
	return (k - 1);
}
