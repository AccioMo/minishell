/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:12:42 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/07 19:26:36 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_add_token(char *str, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_stage_three(char *str, int end, t_token **token, t_env *env)
{
	char	*word;
	int		i;

	i = 0;
	while (i < end)
	{
		if (!ft_strncmp(&str[i], ">", 1))
		{
			ft_add_token(">", 1);
			ft_stage_two(&str[i + 1], end, &(*token)->right, env);
			ft_stage_three(str, i, &(*token)->left, env);
			return ;
		}
		else if (!ft_strncmp(&str[i], "<", 1))
		{
			ft_add_token("<", 1);
			ft_stage_two(&str[i + 1], end, &(*token)->right, env);
			ft_stage_three(str, i, &(*token)->left, env);
			return ;
		}
		else
		{
			word = ft_cp_word(&str[i]);
			// ft_add_token(word, ft_word_len(&str[i]), env->root);
		}
		i++;
	}
}

void	ft_stage_two(char *str, char *end, t_token **token, t_env *env)
{
	int	i;

	i = 0;
	while (&str[i] != end)
	{
		if (!ft_strncmp(&str[i], "|", 1))
		{
			ft_add_token("|", 1);
			ft_stage_two(&str[i + 1], end, &(*token)->right, env);
			ft_stage_three(str, i, &(*token)->left, env);
			return ;
		}
		i++;
	}
	ft_stage_three(str, i, token, env);
}

void	ft_stage_one(char *str, t_token **token, t_env *env)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "&&", 2))
		{
			ft_add_token("&&", 2);
			ft_stage_one(&str[i + 2], &(*token)->right, env);
			ft_stage_two(str, &str[i], &(*token)->left, env);
			return ;
		}
		else if (!ft_strncmp(&str[i], "||", 2))
		{
			ft_add_token("||", 2);
			ft_stage_one(&str[i + 2], &(*token)->right, env);
			ft_stage_two(str, &str[i], &(*token)->left, env);
			return ;
		}
		i++;
	}
	ft_stage_two(str, &str[i], &(*token)->right, env);
}
