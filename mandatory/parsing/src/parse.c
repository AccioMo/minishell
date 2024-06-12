/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:29:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/12 20:16:22 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_free_tree(t_token *token)
{
	if (!token)
		return ;
	if (token->left)
		ft_free_tree(token->left);
	if (token->right)
		ft_free_tree(token->right);
	ft_free(token->args);
	free(token);
}

int	ft_open_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			while (line[++i] && line[i] != '\'')
				;
			if (!line[i])
				return (1);
		}
		else if (line[i] == '\"')
		{
			while (line[++i] && line[i] != '\"')
				;
			if (!line[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_open_parentheses(char *line)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			i += ft_index(&line[i + 1], '\"') + 1;
		else if (line[i] == '\'')
			i += ft_index(&line[i + 1], '\'') + 1;
		else if (line[i] == '(')
			p++;
		else if (line[i] == ')')
			p--;
		i++;
	}
	return (p);
}

int	valid_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_whitespace(line[i]))
			return (1);
		i++;
	}
	free(line);
	return (0);
}

int	ft_get_heredocs(t_token *token, t_shell *shell)
{
	t_heredoc	*heredocs;
	int			ret;

	ret = 0;
	if (!token)
		return (ret);
	if (token->type == REDIR_HEREDOC)
	{
		if (!shell->heredocs)
		{
			shell->heredocs = (t_heredoc *)malloc(sizeof(t_heredoc));
			if (!shell->heredocs)
				return (1);
			if (token->left && token->left->args)
				shell->heredocs->fd = ft_redir_heredoc_function(token->left->args[0], shell);
			else
				shell->heredocs->fd = -1;
			shell->heredocs->next = NULL;
		}
		else
		{
			heredocs = shell->heredocs;
			while (heredocs->next)
				heredocs = heredocs->next;
			heredocs->next = (t_heredoc *)malloc(sizeof(t_heredoc));
			if (!heredocs->next)
				return (1);
			if (token->left && token->left->args)
				shell->heredocs->fd = ft_redir_heredoc_function(token->left->args[0], shell);
			else
				shell->heredocs->fd = -1;
			heredocs->next->next = NULL;
		}
	}
	if (token->left)
		ret = ft_get_heredocs(token->left, shell);
	if (token->right)
		ret = ft_get_heredocs(token->right, shell);
	return (ret);
}

void	ft_clear_heredocs(t_heredoc *heredocs)
{
	t_heredoc	*tmp;

	while (heredocs)
	{
		tmp = heredocs;
		heredocs = heredocs->next;
		close(tmp->fd);
		free(tmp);
	}
}

int	ft_parse(char *line, t_shell *shell)
{
	int		status;
	int		i;

	i = 0;
	if (ft_open_quotes(line) || ft_open_parentheses(line))
	{
		shell->exit_code = set_exit_code(ft_throw_syntax_error(line), true);
		shell->root = NULL;
		free(line);
		return (EXIT_FAILURE);
	}
	status = ft_stage_and(line, &shell->root);
	if (ft_get_heredocs(shell->root, shell))
		status = 1;
	free(line);
	if (status)
	{
		ft_free_tree(shell->root);
		shell->exit_code = set_exit_code(status, true);
		shell->root = NULL;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
