/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/13 19:40:00 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"

int		ft_parse(char *line, t_shell *shell);
int		ft_whitespace(char c);
void	ft_stage_one(char *str, t_token **token);
int		ft_index(char *str, char c);
int		ft_rev_index(char *str, char c);
int		ft_word_len(char *str);
char	*ft_first_word(char *str);
char	*ft_merge(char *part_one, int limit_one, char *part_two, int limit_two);
char	**ft_cmd_split(char *str);
void	ft_free(char **ptr);

void	ft_print_tree(t_token *token);

//	EXEC DRAFT
int		stage_one_function(t_token *token, int fdin, int fdout, t_shell *shell);
int		stage_two_function(t_token *token, int fdin, int fdout, t_shell *shell);
int		stage_three_function(t_token *token, int fdin, int fdout, t_shell *shell);
int		stage_four_function(t_token *token, int fdin, int fdout, t_shell *shell);
int		and_function(t_token *token, int fdin, int fdout, t_shell *shell);
int		or_function(t_token *token, int fdin, int fdout, t_shell *shell);
int		pipe_function(t_token *token, int fdin, int fdout, t_shell *shell);
int		exec_function(t_token *token, int fdin, int fdout, t_shell *shell);
int		redir_in_function(t_token *token, t_shell *shell);
int		redir_out_function(t_token *token, t_shell *shell);
int		redir_append_function(t_token *token, t_shell *shell);
int		redir_heredoc_function(t_token *token, t_shell *shell);

#endif
