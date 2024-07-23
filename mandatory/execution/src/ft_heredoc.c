/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:27:06 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/18 10:18:53 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	sig_herdoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		g_signal = SIGINT;
	}
	return ;
}

static int	ft_heredoc_content(int start, int stdin_copy, t_token *token)
{
	if (g_signal == SIGINT)
	{
		token->fd = -1;
		dup2(stdin_copy, 0);
		close(stdin_copy);
		close(start);
		signal(SIGINT, &main_sig_handler);
		g_signal = 0;
		return (-1);
	}
	signal(SIGINT, &main_sig_handler);
	close(stdin_copy);
	token->fd = start;
	return (start);
}

char	*ft_heredoc_variables(char *str, t_shell *shell)
{
	char	*tmp;
	char	*new;

	new = NULL;
	while (*str)
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
			free(tmp);
			str++;
		}
	}
	return (new);
}

static void	ft_heredoc_loop(char *delimiter, int heredoc_file)
{
	char	*buffer;

	buffer = NULL;
	while (true)
	{
		buffer = readline("> ");
		if (!buffer)
			break ;
		if (!ft_strncmp(buffer, delimiter, ft_strlen(delimiter) + 1))
			break ;
		ft_putstr_fd(buffer, heredoc_file);
		ft_putstr_fd("\n", heredoc_file);
		free(buffer);
	}
	free(buffer);
}

int	ft_open_heredoc(t_token *token)
{
	int		stdin_copy;
	int		end[2];

	g_signal = 0;
	stdin_copy = dup(0);
	if (pipe(end) == -1)
		return (ft_perror("pipe", errno));
	signal(SIGINT, sig_herdoc_handler);
	ft_heredoc_loop(token->args[0], end[1]);
	close(end[1]);
	return (ft_heredoc_content(end[0], stdin_copy, token));
}
