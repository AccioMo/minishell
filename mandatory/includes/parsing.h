/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/09 21:02:56 by mzeggaf          ###   ########.fr       */
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

#endif
