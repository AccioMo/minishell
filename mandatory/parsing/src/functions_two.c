/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:20:34 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/21 07:51:16 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_last(char **array)
{
	char	*word;
	int		i;

	i = 0;
	while (array[i])
		i++;
	word = ft_strdup(array[i]);
	ft_free(array);
	return (word);
}

// char	*ft_expand_vars(char *word, char *value, t_shell *shell)//had if else khashom function lkol whda
// {
// 	int	j;
// 	char * var;

// 	j = 0;
// 	if (word[0] == '?')
// 	{
// 		var = ft_itoa(shell->exit_status);
// 		if (!var)
// 			return (NULL);
// 		value = ft_strjoin(value, var);
// 		if (!value)
// 			return (NULL);
// 		if (word[1] != '\0')
// 			value = ft_strjoin(value, &word[1]);
// 		free(var);
// 	}
// 	// else if (word[0] == '$'/* && word[1] != '$'*/)//khas nhandler ila kant $$$$$$$$$ ntl3olo error... + khasni nhandle l2ar9am .e.g: $234hgjehrghe ==> hgjehrghe
// 	// {//wait acctualy hadi anchofha f split ila returni NULL y3ni string 3amr ghir bhado but how do we know if its only one $ hmmmmmmm,,, handled √
// 	// 	var = ft_strdup("$");
// 	// 	if (!var)
// 	// 		return (NULL);
// 	// 	value = ft_strjoin(value, var);
// 	// 	if (!value)
// 	// 		return (NULL);
// 	// 	free(var);
// 	// }//matms7ch hadchi i feel somthing stupid in it
// 	else
// 	{
// 		var = ft_strdup(ft_getenv(word, shell->env));
// 		if (!var)
// 			return (NULL);
// 		value = ft_strjoin(value, var);
// 		if (!value)
// 			return (NULL);
// 		free(var);
// 	}
// 	return (value);
// }

// char	*ft_extract_variable(char *word, t_shell *shell)
// {
// 	int 	i;
// 	int 	j;
// 	char	*value;
// 	char	**tmp;

// 	i = 0;
// 	j = -1;
// 	value = malloc(sizeof(char) * ft_strlen(word) + 1);
// 	if (!value)
// 		return (NULL);
// 	while (word[i] && word[i] != '$')
// 	{
// 		value[i] = word[i];
// 		i++;	
// 	}
// 	value[i] = '\0';
// 	if (word[i] == '$' && word[i + 1] == '\0')
// 	{
// 		value[i] = '$';
// 		value[i + 1] = '\0';
// 		return (value);
// 	}
// 	else
// 	{
// 		tmp = ft_split(&word[i + 1], '$');
// 		if (!tmp)
// 			return (NULL);
// 		while (tmp[++j])
// 		{
// 			value = ft_expand_vars(tmp[j], value, shell);
// 			if (tmp[j] == NULL)
// 				return (ft_free(tmp), NULL);
// 		}
// 	}
// 	return (value);
// }

// void	ft_realoccate_args(char ***args, int i)
// {
// 	char	**old_args;
// 	char	**args_i;
// 	char	**new_args;
// 	int		j;
// 	int		x;
// 	int		new_size;

// 	old_args = copy_env(*args);
// 	if (!old_args)
// 		return;
// 	args_i = ft_split(old_args[i], ' ');
// 	if (!args_i)
// 	{
// 		ft_free(old_args);
// 		return;
// 	}
// 	new_size = ft_two_d_len(old_args);
// 	x = 0;
// 	while (args_i[x])
// 		x++;
// 	new_size = new_size - 1 + x;
// 	new_args = malloc(sizeof(char *) * (new_size + 1));
// 	if (!new_args)
// 	{
// 		ft_free(old_args);
// 		ft_free(args_i);
// 		return;
// 	}
// 	j = 0;
// 	while (j < i)
// 	{
// 		new_args[j] = ft_strdup(old_args[j]);
// 		if (!new_args[j])
// 		{
// 			ft_free(new_args);
// 			ft_free(old_args);
// 			ft_free(args_i);
// 			return;
// 		}
// 		j++;
// 	}
// 	// Copy split args from args_i hado homa li kant fihom * w expanditha..
// 	x = 0;
// 	while (args_i[x])
// 	{
// 		new_args[j] = ft_strdup(args_i[x]);
// 		if (!new_args[j])
// 		{
// 			ft_free(new_args);
// 			ft_free(old_args);
// 			ft_free(args_i);
// 			return;
// 		}
// 		j++;
// 		x++;
// 	}
// 	// Copy the rest of old args after index i
// 	i++;  // Skip the current i li kant fih * w expanditha.
// 	while (old_args[i])
// 	{
// 		new_args[j] = ft_strdup(old_args[i]);
// 		if (!new_args[j])
// 		{
// 			ft_free(new_args);
// 			ft_free(old_args);
// 			ft_free(args_i);
// 			return;
// 		}
// 		j++;
// 		i++;
// 	}
// 	new_args[j] = NULL;
// 	ft_free(old_args);
// 	ft_free(args_i);
// 	free(*args);
// 	*args = new_args;
// }

// void	ft_handle_wildecard(t_token *token, int i)
// {
// 	DIR		*dir;
// 	struct dirent	*entry;
// 	char	*dirname;
// 	char	cwd[255];
// 	char *tmp;

// 	entry = NULL;
// 	dirname = ft_strdup(getcwd(cwd, 255));//hna khasni ndir strjoin l token->args[i] w * ila makantch * 
// 	if (!dirname)
// 		return ;//error managing...
// 	dir = opendir(dirname);
// 	if (!dir)
// 	{
// 		free(dirname);
// 		return ;
// 	}
// 	entry = readdir(dir);
// 	if (!entry)
// 	{
// 		free(dirname);
// 		closedir(dir);
// 		return ;
// 	}
// 	// ft_printf("Files in %s:\n", dirname);
// 	tmp = ft_strdup("");
// 	while (entry)
// 	{
// 		if (entry->d_name[0] == '.')
// 		{
// 			entry = readdir(dir);
// 			continue ;
// 		}
// 		// ft_printf("%s\n", entry->d_name);
// 		tmp = ft_strjoin(tmp, entry->d_name);
// 		if (!tmp)
// 			return ;//error managing...
// 		tmp = ft_strjoin(tmp, " ");
// 		if (!tmp)
// 			return ;
// 		entry = readdir(dir);
// 	}
// 	// ft_printf("tmp: %s\n", tmp);//khedama daba wa2akhiran. but hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh khas npasiha ka 2d array hhhhhhhh fuck: Update done azbi wakha mokhi kit7r9 db
// 	free(token->args[i]);
// 	token->args[i] = tmp;
// 	closedir(dir);
// }

// int	ft_late_work(t_token *token, t_shell *shell)
// {
// 	int		i;

// 	i = 0;
// 	if (token->left)
// 		ft_late_work(token->left, shell);
// 	if (token->right)
// 		ft_late_work(token->right, shell);
// 	if (token->type == WORD)
// 	{
// 		while (token->args[i])
// 		{
// 			if (token->args[i][0] == '*' && token->args[i][1] == '\0')
// 			{
// 				ft_handle_wildecard(token, i);
// 				ft_realoccate_args(&token->args, i);
// 				i++;
// 				continue ;
// 			}
// 			if (!ft_strchr(token->args[i], '$'))
// 			{
// 				i++;
// 				continue ;
// 			}
// 			token->args[i] = ft_extract_variable(token->args[i], shell);
// 			if (!token->args[i])
// 				return (1);//malloc error
// 			i++;
// 		}
// 	}
// 	return (0);
// }
