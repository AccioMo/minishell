/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:40:33 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/26 15:12:56 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static int	ft_hd_redirect_output(char **cmds, int fdin, char **env)
{
	int	end[2];

	if (pipe(end) < 0)
	{
		close(fdin);
		perror("pipe");
		return (EXIT_FAILURE);
	}
	close(end[1]);
	end[1] = open(*(cmds + 1), O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (end[1] < 0)
	{
		close(fdin);
		close(end[0]);
		perror(*(cmds + 1));
		return (EXIT_FAILURE);
	}
	ft_exec_cmd(*cmds, env, fdin, end);
	close(fdin);
	close(end[1]);
	close(end[0]);
	return (EXIT_SUCCESS);
}

static int	ft_here_doc_pipe(char **cmds, int fdin, char **env)
{
	int		end[2];

	while (*(cmds + 2))
	{
		if (pipe(end) < 0)
		{
			close(fdin);
			perror("pipe");
			return (EXIT_FAILURE);
		}
		ft_exec_cmd(*cmds, env, fdin, end);
		close(fdin);
		fdin = dup(end[0]);
		close(end[1]);
		close(end[0]);
		if (fdin < 0)
		{
			perror("dup");
			return (EXIT_FAILURE);
		}
		cmds++;
	}
	fdin = ft_hd_redirect_output(cmds, fdin, env);
	return (fdin);
}

int	ft_here_doc(char **args, char **env)
{
	char	*buffer;
	char	*input;
	int		fd[2];

	input = NULL;
	buffer = NULL;
	while (is_limiter(buffer, *args) == 0)
	{
		input = ft_realloc(input, buffer);
		free(buffer);
		ft_putstr_fd("pipe heredoc> ", 1);
		buffer = get_next_line(0);
		if (!buffer)
			break ;
	}
	free(buffer);
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(input, fd[1]);
	free(input);
	close(fd[1]);
	return (ft_here_doc_pipe(args + 1, fd[0], env));
}
