/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:01:47 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/07/10 00:14:59 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include "minishell.h"
# include "readline/readline.h"
# include "readline/history.h"

int			ft_parse(char *line, t_shell *shell);
int			ft_stage_and(char *str, t_token **token);
int			ft_word_len(char *str);
char		*ft_merge(char *part_one, int l_1, char *part_two, int l_2);
char		**ft_cmd_split(char *str);
int			ft_skip_parentheses(char *str);
int			ft_reserved_word(char *str);
int			ft_throw_syntax_error(char *word);
void		ft_free(char **ptr);

t_token		*ft_add_token(t_type type, t_token **token);
int			ft_skip_parentheses(char *str);
int			ft_stage_exec(char *str, int end, t_token **token);
int			ft_stage_redir(char *str, int end, t_token **token);
int			ft_stage_pipe(char *str, int end, t_token **token);
int			ft_stage_or(char *str, int end, t_token **token);
int			ft_stage_and(char *str, t_token **token);

char		**ft_append_to_array(char **args, char *new_arg);
int			ft_variables(char *str, t_token *token, t_shell *shell);
int			valid_line(char *line);
char		*ft_wildcard(char *pattern, t_token *token);
int			ft_variable_length(char *str);
char		*ft_wildcard_match(char *pattern, char *str);
char		*ft_quotes_wildcard(char *pattern, t_shell *shell);
char		*ft_split_variable(char *str, char *new, t_token *tok, t_shell *sh);
char		*ft_quoted_variables(char *str, t_shell *shell);
char		*ft_remove_wd_backslash(char *str);
char		*ft_backslash_wildcard(char *str);
char		*ft_remove_quotes(char *str);
int			ft_stage_and(char *str, t_token **token);
int			ft_stage_exec(char *str, int end, t_token **token);
int			ft_handle_and(char *str, int end, t_token **token);
int			ft_handle_parentheses(char *str, int end, t_token **token);
int			ft_parse_word(char *str, int end, t_token **token);
char    	*ft_single_quotes_wildcard(char *pattern, int i);
int	        ft_found_token(char *str, char c);
char		**ft_wildcard_split(char *str);
char		*ft_var_backslash_wildcard(char *str);

#endif
