/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/10 19:40:08 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

int		ft_parse(char *line, t_shell *shell);
int		ft_whitespace(char c);
void	ft_stage_one(char *str, t_token **token);
int		ft_rindex(char *str, char c);
int		ft_word_len(char *str);
char	*ft_first_word(char *str);
char	*ft_merge(char *part_one, int limit_one, char *part_two, int limit_two);
char	**ft_cmd_split(char *str);
void	ft_free(char **ptr);

#endif
