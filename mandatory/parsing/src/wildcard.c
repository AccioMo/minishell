/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:36:54 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/11 16:47:00 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_quotes_wildcard(char *pattern, t_shell *shell)
{
	char	*tmp;
	int 	pe;

	pe = ft_index(pattern, '\"');
	tmp = ft_substr(pattern, 0, pe);
	if (ft_contains_variable(tmp))
	{
		pattern += pe + 1;
		tmp = ft_quoted_variables(tmp, shell);
		pattern = ft_strjoin(tmp, pattern);
		pe = ft_strlen(tmp);
	}
	free(tmp);
	return (pattern);
}

int	ft_found_wildcard(char *pattern)
{
	int	i;

	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == '*' && (i == 0 || pattern[i - 1] != '\\'))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_handle_wildcard(char *pattern, int *i, char **str)
{
	char	*tmp_str;

	tmp_str = *str;
	if (ft_strncmp(tmp_str, pattern, *i))
		return (NULL);
	pattern += *i;
	while (!ft_strncmp(pattern, "\\*", 2))
		pattern += 2;
	if (!ft_strstr(pattern, "\\*"))
	{
		if (ft_strlen(pattern) > ft_strlen(tmp_str))
			return (NULL);
		tmp_str += (ft_strlen(tmp_str) - ft_strlen(pattern));
		*str = tmp_str;
		*i = 0;
		return (pattern);
	}
	while (*tmp_str && *tmp_str != *pattern)
		tmp_str++;
	*i = 0;
	*str = tmp_str;
	return (pattern);
}

char	*ft_single_quotes_wildcard(char *pattern, int i)
{
	char	*tmp;
	int		pe;

	pe = ft_index(&pattern[i + 1], '\'') + 1;
	tmp = ft_substr(&pattern[i + 1], 0, pe);
	pattern = ft_substr(pattern, i, pe);
	pattern = ft_realloc(pattern, tmp);
	free(tmp);
	return (pattern);
}

char	*ft_wildcard_variable(char *pattern, int *i, t_token *token, t_shell *shell)
{
	char	*vars;
	char	*tmp;
	int		pe;

	tmp = ft_substr(pattern, 0, *i);
	vars = ft_split_variable(&pattern[*i], tmp, token, shell);
	pe = *i + ft_variable_length(&pattern[*i]);
	*i = ft_strlen(vars);
	pattern = ft_realloc(vars, &pattern[pe]);
	return (pattern);
}

char	*ft_wildcard_match(char *pattern, char *str)
{
	int		i;

	i = 0;
	while (pattern[i])
	{
		if (!ft_strncmp(&pattern[i], "\\*", 2))
			pattern = ft_handle_wildcard(pattern, &i, &str);
		else
			i++;
		if (!pattern)
			return (0);
	}
	if (str && ft_strncmp(str, pattern, i))
		return (0);
	return (pattern);
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

char	*ft_wildcard(char *pattern, t_token *token)
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
			&& ft_wildcard_match(pattern, dir_entry->d_name))
		{
			new_arr = ft_append_to_array(new_arr, dir_entry->d_name);
			matches++;
		}
		dir_entry = readdir(dir);
	}
	if (matches == 0)
	{
		pattern = ft_remove_wd_backslash(pattern);
		new_arr = ft_append_to_array(new_arr, pattern);
	}
	// sort_arr(new_arr);
	i = -1;
	while (new_arr[++i])
		token->args = ft_append_to_array(token->args, new_arr[i]);
	closedir(dir);
	return (NULL);
}
