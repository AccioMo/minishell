/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:55:31 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/30 18:17:34 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_clean_nulls(t_token *token)
{
	char **new_args;
	int  i;
	int  j;

	i = -1;
	j = 0;
	while (++i < ft_array_len(token->args))
		if (token->args[i])
			j++;
	new_args = (char **)malloc(sizeof(char *) * (j + 1));
	if (new_args)
		return (EXIT_FAILURE); // malloc error
	new_args[j] = NULL;
	i = -1;
	j = 0;
	while (++i < ft_array_len(token->args))
	{
		if (token->args[i])
		{
			new_args[j] = ft_strdup(token->args[i]);
			if (!new_args[j])
				return (ft_free(new_args), EXIT_FAILURE);
			j++;
		}
	}
	for (i = 0; token->args[i]; i++)
		printf("%s\n", token->args[i]);
	free(token->args);
	token->args = new_args;
	return (EXIT_SUCCESS);
}
