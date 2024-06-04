/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:36:54 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/04 06:03:56 by zouddach         ###   ########.fr       */
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
	if (!pattern)
		return (0);
	getcwd(cwd, PATH_MAX);
	dir = opendir(cwd);
	if (!dir)
		return (1);
	dir_entry = readdir(dir);
	while (dir_entry)
	{
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
	{
		token->args = ft_remove_from_array(token->args, i);
		k--;
	}
	return (k);
}
