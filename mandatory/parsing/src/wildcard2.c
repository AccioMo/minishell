/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:53:38 by zouddach          #+#    #+#             */
/*   Updated: 2024/06/09 11:12:29 by zouddach         ###   ########.fr       */
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

void    sort_arr(char **oldbuff)
{
    char    *str_one;
    int     i;
    int     swapped;
    int     oldBuffSize;

    if (oldbuff == NULL)
        return ;
    oldBuffSize = ft_array_len(oldbuff);
    swapped = 1;
    while (swapped)
    {
        swapped = 0;
        i = 0;
        while (i < oldBuffSize - 1)
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

char	**ft_append_to_array(char **args, char *new_arg)
{
	char	**new_args;
	int		i;

	i = 0;
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
	while (args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = ft_strdup(new_arg);
	if (!new_args[i])
	{
		ft_free(new_args);
		return (NULL);
	}
	new_args[i + 1] = NULL;
	free(args);
	return (new_args);
}
