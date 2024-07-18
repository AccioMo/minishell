/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 07:36:54 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/18 11:19:40 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

char	*ft_quotes_wildcard(char *pattern, t_shell *shell)
{
	char	*tmp;
	int		pe;

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

char	*ft_wildcard_variable(char *pattern, int *i,
	t_token *token, t_shell *shell)
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

void	ft_wildcard_continue(DIR *dir, struct dirent
	*dir_entry, char ***new_arr, char **pattern)
{
	int	matches;

	matches = 0;
	while (dir_entry)
	{
		if (!(dir_entry->d_name[0] == '.' && (*pattern)[0] != '.') \
			&& ft_wildcard_match((*pattern), dir_entry->d_name))
		{
			(*new_arr) = ft_append_to_array((*new_arr), dir_entry->d_name);
			matches++;
		}
		dir_entry = readdir(dir);
	}
	if (matches == 0)
	{
		(*pattern) = ft_remove_wd_backslash(ft_strdup((*pattern)));
		(*new_arr) = ft_append_to_array((*new_arr), (*pattern));
		free((*pattern));
	}
	sort_arr((*new_arr));
}

char	*ft_wildcard(char *pattern, t_token *token)
{
	struct dirent	*dir_entry;
	DIR				*dir;
	char			**new_arr;
	int				i;

	if (!pattern)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	dir_entry = readdir(dir);
	new_arr = NULL;
	ft_wildcard_continue(dir, dir_entry, &new_arr, &pattern);
	i = -1;
	while (new_arr[++i])
		token->args = ft_append_to_array(token->args, new_arr[i]);
	ft_free(new_arr);
	closedir(dir);
	return (NULL);
}
