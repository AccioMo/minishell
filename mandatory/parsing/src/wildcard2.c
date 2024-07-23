/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:53:38 by zouddach          #+#    #+#             */
/*   Updated: 2024/07/23 02:48:27 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**ft_remove_from_array(char **array, int x)
{
	char	**new_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!array)
		return (NULL);
	while (array[i])
		i++;
	new_array = (char **)malloc(sizeof(char *) * i);
	if (!new_array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		if (i == x)
			free(array[i++]);
		else
			new_array[j++] = array[i++];
	}
	new_array[j] = NULL;
	free(array);
	return (new_array);
}

void	sort_arr(char **oldbuff)
{
	char	*str_one;
	int		i;
	int		swapped;
	int		old_buff_size;

	if (oldbuff == NULL)
		return ;
	old_buff_size = ft_array_len(oldbuff);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < old_buff_size - 1)
		{
			if (strcmp(oldbuff[i], oldbuff[i + 1]) > 0)
			{
				str_one = oldbuff[i];
				oldbuff[i] = oldbuff[i + 1];
				oldbuff[i + 1] = str_one;
				swapped = 1;
			}
			i++;
		}
	}
}

int	ft_append_to_array_2(char ***args, int i,
	char ***new_args, char **new_arg)
{
	while ((*args)[i])
		i++;
	(*new_args) = malloc(sizeof(char *) * (i + 2));
	if (!(*new_args))
		return (0);
	i = 0;
	while ((*args)[i])
	{
		(*new_args)[i] = (*args)[i];
		i++;
	}
	(*new_args)[i] = ft_strdup(*new_arg);
	if (!(*new_args)[i])
	{
		ft_free((*new_args));
		return (0);
	}
	(*new_args)[i + 1] = NULL;
	return (1);
}

char	**ft_append_to_array(char **args, char *new_arg)
{
	char	**new_args;
	int		i;

	i = 0;
	new_args = NULL;
	if (!new_arg)
		return (args);
	if (!args)
	{
		new_args = (char **)malloc(sizeof(char *) * 2);
		if (!new_args)
			return (NULL);
		new_args[0] = ft_strdup(new_arg);
		if (!new_args[0])
		{
			free(new_args);
			return (NULL);
		}
		new_args[1] = NULL;
		return (new_args);
	}
	if (ft_append_to_array_2(&args, i, &new_args, &new_arg) == 0)
		return (NULL);
	free(args);
	return (new_args);
}
