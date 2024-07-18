/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:29:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/07/18 11:19:40 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

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

// int	ft_get_heredoc(t_token *token, t_shell *shell)
// {
// 	int			ret;

// 	ret = 0;
// 	if (!token)
// 		return (ret);
// 	if (token->type == REDIR_HEREDOC && token->left && token->left->args)
// 		close(ft_redir_heredoc_function(token->left, shell));
// 	if (token->left)
// 		ret = ft_get_heredocs(token->left, shell);
// 	if (token->right)
// 		ret = ft_get_heredocs(token->right, shell);
// 	return (ret);
// }

int	ft_parse(char *line, t_shell *shell)
{
	int		status;
	int		i;

	i = 0;
	status = ft_stage_and(line, &shell->root);
	free(line);
	if (status)
	{
		if (status == PARSING_FAILURE)
			ft_throw_syntax_error(NULL);
		ft_free_tree(shell->root);
		shell->exit_code = set_exit_code(status, true);
		shell->root = NULL;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
