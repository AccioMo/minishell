/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:12:42 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/06 20:12:01 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_stage_one(char *str, t_env *env)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "&&", 2))
		{
			ft_add_token(AND, "&&", env);
			ft_stage_two(str, i, env);
			ft_stage_one(&str[i + 2], env);
		}
		else if (!ft_strncmp(&str[i], "||", 2))
		{
			ft_add_token(OR, "||", env);
			ft_stage_two(str, i, env);
			ft_stage_one(&str[i + 2], env);
		}
		i++;
	}
}