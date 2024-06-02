/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:15:21 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/01 16:56:15 by mzeggaf          ###   ########.fr       */
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

int	ft_redir_in_function(t_token *token)
{
	int	fd;

	fd = open(token->args[0], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

int	ft_redir_out_function(t_token *token)
{
	int	fd;

	fd = open(token->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

int	ft_redir_append_function(t_token *token)
{
	int	fd;

	fd = open(token->args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
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

int	ft_redir_heredoc_function(t_token *token)
{
	char	*buffer;
	char	*input;
	int		stdin_copy;
	int		end[2];

	input = NULL;
	buffer = NULL;
	g_signal = 0;
	stdin_copy = dup(0);
	signal(SIGINT, sig_herdoc_handler);
	while (!is_limiter(buffer, token->args[0]))
	{
		input = ft_realloc(input, buffer);
		free(buffer);
		ft_putstr_fd("> ", 1);
		buffer = get_next_line(0);
		if (!buffer)
			break ;
	}
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
