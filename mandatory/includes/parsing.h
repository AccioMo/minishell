/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:01:47 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/22 20:45:10 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <termios.h>
# include "minishell.h"
# include "readline/readline.h"
# include "readline/history.h"

int		ft_parse(char *line, t_shell *shell);
int		ft_stage_one(char *str, t_token **token);
int		ft_rev_index(char *str, char c);
int		ft_word_len(char *str);
char	*ft_first_word(char *str);
char	*ft_merge(char *part_one, int limit_one, char *part_two, int limit_two);
char	**ft_cmd_split(char *str);
int		ft_skip_parentheses(char *str);
int		ft_throw_error(char *msg, char *word);
void	ft_free(char **ptr);

void	ft_print_tree(t_token *token);

#endif
