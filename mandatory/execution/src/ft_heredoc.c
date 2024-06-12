/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:27:06 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/12 20:18:38 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// static int	is_limiter(char *str, char *limiter)
// {
// 	int	ret;
// 	int	len;

// 	if (!str || !limiter)
// 		return (0);
// 	len = ft_strlen(limiter);
// 	ret = ft_strncmp(str, limiter, len);
// 	if (!ret && *(str + len) == '\n')
// 		return (1);
// 	return (0);
// }

void	sig_herdoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		g_signal = SIGINT;
	}
	return ;
}

int	ft_heredoc_content(int start, int stdin_copy)
{
	if (g_signal == SIGINT)
	{
		dup2(stdin_copy, 0);
		close(stdin_copy);
		close(start);
		signal(SIGINT, &sig_handler);
		return (-1);
	}
	close(stdin_copy);
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
			str++;
		}
	}
	return (new);
}

int	ft_redir_heredoc_function(char *limiter, t_shell *shell)
{
	char	*buffer;
	int		start;
	int		stdin_copy;
	int		heredoc_file;

	buffer = NULL;
	limiter = ft_remove_quotes(ft_strdup(limiter));
	if (!limiter)
		return (-1);
	g_signal = 0;
	stdin_copy = dup(0);
	heredoc_file = open("/tmp/heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	start = open("/tmp/heredoc", O_RDONLY);
	unlink("/tmp/heredoc");
	signal(SIGINT, sig_herdoc_handler);
	while (!buffer || ft_strncmp(buffer, limiter, -1))
	{
		free(buffer);
		buffer = readline("> ");
		if (!buffer)
			break ;
		if (ft_contains_variable(buffer))
			buffer = ft_heredoc_variables(buffer, shell);
		ft_putstr_fd(buffer, heredoc_file);
		ft_putstr_fd("\n", heredoc_file);
	}
	free(buffer);
	close(heredoc_file);
	return (ft_heredoc_content(start, stdin_copy));
}
