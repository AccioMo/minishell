/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:36:54 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/08 17:54:00 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_widcard_match(char *pattern, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (pattern[i])
	{
		if (pattern[i] == '\"')
			i += ft_index(&pattern[i + 1], '\"') + 2; // could cause segfault
		else if (pattern[i] == '\'')
			i += ft_index(&pattern[i + 1], '\'') + 2;
		else if (pattern[i] == 42)
		{
			while (pattern[i] == 42)
				i++;
			while (str[j] && pattern[i] != str[j])
				j++;
		}
		else if (pattern[i] != str[j])
			return (0);
		else
		{
			j++;
			i++;
		}
	}
	return (1);
}

int	ft_handle_wildecard(t_token *token, char *pattern)
{
	struct dirent	*dir_entry;
	char			cwd[PATH_MAX];
	DIR				*dir;
	int				matches;

	matches = 0;
	pattern = ft_remove_quotes(pattern);
	if (!pattern)
		return (0);
	dir = opendir(cwd);
	if (!dir)
		return (1);
	dir_entry = readdir(dir);
	while (dir_entry)
	{
		if ((dir_entry->d_name[0] != '.' || pattern[0] == '.') && \
			ft_widcard_match(pattern, dir_entry->d_name) == 1)
		{
			token->args = ft_append_to_array(token->args, dir_entry->d_name);
			matches++;
		}
		dir_entry = readdir(dir);
	}
	closedir(dir);
	return (0);
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
		j++;
	}
	return (0);
}

char	*ft_wildcard(t_token *token, char *pattern)
{
	struct dirent	*dir_entry;
	DIR				*dir;
    char            **new_arr;
	int				matches;
	int				i;

	matches = 0;
	if (!pattern)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	dir_entry = readdir(dir);
	new_arr = NULL;
	while (dir_entry)
	{
		if (!(dir_entry->d_name[0] == '.' && pattern[0] != '.') \
			&& ft_widcard_match(pattern, dir_entry->d_name) == 1)
		{
			new_arr = ft_append_to_array(new_arr, dir_entry->d_name);
			matches++;
		}
		dir_entry = readdir(dir);
	}
	if (matches == 0)
		new_arr = ft_append_to_array(new_arr, pattern);
	sort_arr(new_arr);
	i = -1;
	while (new_arr[++i])
		token->args = ft_append_to_array(token->args, new_arr[i]);
	closedir(dir);
	return (NULL);
}
