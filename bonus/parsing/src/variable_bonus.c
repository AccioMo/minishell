/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:17:30 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/07/23 02:30:44 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

int	ft_variable_length(char *str)
{
	int	len;

	len = 0;
	if (ft_isdigit(str[len]))
		return (1);
	else if (str[len] == '?')
		return (1);
	else if (str[len] == '_')
		return (1);
	else if (ft_isalnum(str[len]))
	{
		while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
			len++;
		return (len);
	}
	return (0);
}

char	*ft_expand_variable(char *str, t_shell *shell)
{
	char	*tmp;
	char	*new;
	int		len;

	if (ft_isdigit(*str) || *str == '\"' || *str == '\'')
		return (NULL);
	else if (*str == '?')
		return (ft_itoa(shell->exit_code));
	else if (*str == '_')
		return (ft_strdup(ft_getenv("_", shell->env)));
	else if (ft_isalnum(*str))
	{
		len = 0;
		while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
			len++;
		tmp = ft_substr(str, 0, len);
		new = ft_getenv(tmp, shell->env);
		free(tmp);
		return (ft_strdup(new));
	}
	return (ft_strdup("$"));
}

int	ft_contains_variable(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i += ft_index(&str[i + 1], "\'") + 1;
		else if (str[i] == '\"')
		{
			while (str[++i] && str[i] != '\"')
			{
				if (str[i] == '$')
					return (1);
			}
		}
		else if (str[i] == '$' && str[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_quoted_variables(char *str, t_shell *shell)
{
	char	*tmp;
	char	*new;

	new = NULL;
	while (*str && *str != '\"')
	{
		if (*str == '$' && (ft_isalnum(*(str + 1)) || \
			ft_strchr("?_", *(str + 1))))
		{
			tmp = ft_expand_variable(++str, shell);
			new = ft_realloc(new, tmp);
			free(tmp);
			str += ft_variable_length(str);
		}
		else
		{
			tmp = ft_substr(str, 0, 1);
			new = ft_realloc(new, tmp);
			str++;
		}
	}
	return (new);
}

int	ft_expand_heredoc(t_token *token, t_shell *shell)
{
	char	*buffer;
	char	*tmp;
	int		end[2];

	if (pipe(end) == -1)
		return (ft_perror("pipe", errno));
	buffer = get_next_line(token->fd);
	while (buffer)
	{
		if (ft_contains_variable(buffer))
		{
			tmp = ft_heredoc_variables(buffer, shell);
			ft_putstr_fd(tmp, end[1]);
			free(tmp);
		}
		else
			ft_putstr_fd(buffer, end[1]);
		free(buffer);
		buffer = get_next_line(token->fd);
	}
	close(token->fd);
	close(end[1]);
	free(buffer);
	return (end[0]);
}
