/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:01:47 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/01 17:54:41 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include "minishell.h"
# include "readline/readline.h"
# include "readline/history.h"

int			ft_parse(char *line, t_shell *shell);
int			ft_stage_one(char *str, t_token **token);
int			ft_word_len(char *str);
char		*ft_merge(char *part_one, int l_1, char *part_two, int l_2);
char		**ft_cmd_split(char *str);
int			ft_skip_parentheses(char *str);
int			ft_reserved_word(char *str);
int			ft_throw_syntax_error(char *word);
void		ft_free(char **ptr);

t_token		*ft_add_token(t_type type, char *str, t_token **token);
int			ft_skip_parentheses(char *str);
int			ft_stage_four(char *str, int end, t_token **token);
int			ft_stage_three(char *str, int end, t_token **token);
int			ft_stage_two(char *str, int end, t_token **token);
int			ft_stage_one(char *str, t_token **token);

void	ft_print_tree(t_token *token);

#endif
