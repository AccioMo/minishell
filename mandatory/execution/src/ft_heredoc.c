/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:27:06 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/04 06:04:56 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_limiter(char *str, char *limiter)
{
	int	ret;
	int	len;

	if (!str || !limiter)
		return (0);
	len = ft_strlen(limiter);
	ret = ft_strncmp(str, limiter, len);
	if (!ret && *(str + len) == '\n')
		return (1);
	return (0);
}

void	sig_herdoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		g_signal = SIGINT;
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
	}
	return ;
}

int	ft_heredoc_content(char *input, int stdin_copy)
{
	int		end[2];

	if (g_signal == SIGINT)
	{
		dup2(stdin_copy, 0);
		close(stdin_copy);
		free(input);
		return (-1);
	}
	close(stdin_copy);
	if (pipe(end))
		return (-1);
	ft_putstr_fd(input, end[1]);
	free(input);
	close(end[1]);
	return (end[0]);
}

int	ft_redir_heredoc_function(t_token *token)
{
	char	*buffer;
	char	*input;
	int		stdin_copy;

	input = NULL;
	buffer = NULL;
	g_signal = 0;
	stdin_copy = dup(0);
	signal(SIGINT, sig_herdoc_handler);
	while (!is_limiter(buffer, token->args[0]))
	{
		input = ft_realloc(input, buffer);
		free(buffer);
		buffer = readline("> ");
		if (!buffer)
			break ;
		buffer = ft_realloc(buffer, "\n");
	}
	return (ft_heredoc_content(input, stdin_copy));
}
