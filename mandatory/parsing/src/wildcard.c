/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:36:54 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/10 21:37:41 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_mini_wildcard_match(char *pattern, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (pattern[i])
	{
		if (pattern[i] == 42)
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

char	*ft_handle_wildcard(char *pattern, int *i, char **str, t_shell *shell)
{
	char	*tmp_str;
	int		pe;

	tmp_str = *str;
	if (tmp_str && ft_strncmp(tmp_str, pattern, *i))
		return (NULL);
	pattern += *i;
	while (*pattern == '*')
		pattern++;
	pattern += (*pattern == '\'') || (*pattern == '\"');
	while (tmp_str && *tmp_str && *tmp_str != *pattern)
		tmp_str++;
	if (*(pattern - 1) == '\'')
	{
		pe = ft_index(pattern, '\'');
		if (tmp_str && ft_strncmp(tmp_str, pattern, pe))
			return (NULL);
		pattern += pe + 1;
		tmp_str += pe;
	}
	else if (*(pattern - 1) == '\"')
		pattern = ft_quotes_wildcard(pattern, shell);
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

char	*ft_wildcard_match(char *pattern, char *str, t_token *token, t_shell *shell)
{
	int	i;

	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == '$')
			pattern = ft_wildcard_variable(pattern, &i, token, shell);
		else if (pattern[i] == '*')
			pattern = ft_handle_wildcard(pattern, &i, &str, shell);
		else if (pattern[i] == '\'')
			pattern = ft_single_quotes_wildcard(pattern, i);
		else if (pattern[i] == '\"')
			pattern = ft_realloc(ft_substr(pattern, 0, i), \
				ft_quotes_wildcard(&pattern[i + 1], shell));
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

char	*ft_wildcard(char *pattern, t_token *token, t_shell *shell)
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
			&& ft_wildcard_match(pattern, dir_entry->d_name, token, shell))
		{
			new_arr = ft_append_to_array(new_arr, dir_entry->d_name);
			matches++;
		}
		dir_entry = readdir(dir);
	}
	if (matches == 0)
	{
		pattern = ft_remove_quotes(pattern);
		new_arr = ft_append_to_array(new_arr, pattern);
	}
	// sort_arr(new_arr);
	i = -1;
	while (new_arr[++i])
		token->args = ft_append_to_array(token->args, new_arr[i]);
	closedir(dir);
	return (NULL);
}
