/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:21:15 by zouddach          #+#    #+#             */
/*   Updated: 2024/05/30 20:01:52 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_change_existing_var(t_shell *shell, char *var)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_substr(var, 0, ft_index(var, '=') + 1);
	if (!tmp)
		return (EXIT_FAILURE);
	if (ft_change_env_value(shell->env, tmp, ft_strchr(var, '=') + 1))
	{
		free(tmp);
		return (EXIT_SUCCESS);
	}
	free(tmp);
	return (EXIT_FAILURE);
}

int	ft_var_exist(t_shell *shell, char *var)
{
	char	*tmp;
	int		i;
	int		equal_pos;

	i = 0;
	equal_pos = ft_get_index(var, '=');
	if (equal_pos <= 0)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	tmp = ft_substr(var, 0, ft_get_index(var, '='));
	if (!tmp)
		return (EXIT_FAILURE);
	if (ft_getenv(tmp, shell->env))
	{
		free(tmp);
		if (ft_change_existing_var(shell, var) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (1);
	}
	free(tmp);
	return (0);
}
