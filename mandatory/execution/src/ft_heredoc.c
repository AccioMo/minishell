/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:27:06 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/26 20:13:28 by mzeggaf          ###   ########.fr       */
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
	char	*first_file;
	int		write_fd;
	int		read_fd;

	g_signal = 0;
	stdin_copy = dup(0);
	first_file = ft_itoa((int)token);
	read_fd = open(first_file, O_RDONLY | O_CREAT | O_TRUNC, 0644);
	write_fd = open(first_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (write_fd == -1 || read_fd == -1)
	{
		perror("minishell: open");
		free(first_file);
		ft_close_fds(read_fd, write_fd);
		return (-1);
	}
	unlink(first_file);
	ft_putendl_fd(first_file, 1);
	free(first_file);
	signal(SIGINT, sig_herdoc_handler);
	token->args[0] = ft_remove_quotes(token->args[0]);
	ft_heredoc_loop(token->args[0], write_fd);
	close(write_fd);
	return (ft_heredoc_content(read_fd, stdin_copy, token));
}
