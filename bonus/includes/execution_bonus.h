/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/07/23 02:33:37 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_BONUS_H
# define EXECUTION_BONUS_H

# include "minishell_bonus.h"
# include <sys/stat.h>

int		ft_echo(t_token	*token, int fdout);
int		ft_pwd(int fdout, t_shell *shell);
int		ft_cd(t_token *token, t_shell *env);
int		ft_unset(t_token *token, t_shell *shell);
int		ft_export(t_token *cmd, t_shell *env, int fdout);
int		ft_execute_builtin(t_token *cmd, int fdout, t_shell *env);
int		ft_is_builtin(t_token *token);
int		ft_env(t_list *env, int fdout);
int		ft_get_index(char *str, char c);
int		ft_count_char(char *str, char c);
char	*ft_allocate_cmd(char **cmd, char **env);
char	**ft_get_paths(char **env);
char	*ft_match_path(char *command, char **paths_env);
int		ft_exec_function(t_token *token, int fdin[2], int fdout, t_shell *sh);
int		ft_or_function(t_token *token, int fdin, int fdout, t_shell *shell);
int		ft_and_function(t_token *token, int fdin, int fdout, t_shell *shell);
int		ft_priority_token(t_token *token, int fdin, int fdout, t_shell *shell);
int		ft_redir_token(t_token *token, int fi[2], int fo, t_shell *shell);
int		ft_pipe_token(t_token *token, int fdin, int fdout, t_shell *shell);
int		ft_execution_token(t_token *token, int fdin[2], int fdout, t_shell *sh);
char	*ft_remove_quotes(char *str);
int		ft_expand_variables(t_token *token, t_shell *shell);
int		ft_expand_wildcard(t_token *token);
int		ft_redir_in_function(t_token *token);
int		ft_redir_out_function(t_token *token);
void	sigquit_handler(int signal);
int		ft_exec_error(char *cmd, int code);
void	ft_free(char **ptr);
void	ft_dup_pipes(int fdin[2], int fdout);
char	**ft_list_to_array(t_list *env);
void	ft_close_fds(int fdin, int fdout);
int		ft_handle_redirs_in(t_token *tk, int fi[2], int fo, t_shell *sh);
int		ft_handle_redirs_out(t_token *tk, int fi[2], int fo, t_shell *sh);
int		ft_first_token(t_token *token, int fdin, int fdout, t_shell *shell);

#endif
