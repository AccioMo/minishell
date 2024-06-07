/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/07 12:45:10 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <sys/stat.h>

/*A mimit of echo function with -n option only*/
int		ft_echo(t_token	*token, int fdout);

/*A mimit of pwd function*/
int		ft_pwd(int fdout, t_list *env);

/*A mimit function of cd*/
int		ft_cd(t_token *token, t_shell *env);

/*A mimit function of unset shell-builtin functions*/
int		ft_unset(t_token *token, t_list *env);

/*A mimit function of export shell-builtin functions*/
int		ft_export(t_token *cmd, t_shell *env, int fdout);

/*A function that execute builtin functions*/
int		ft_execute_builtin(t_token *cmd, int fdout, t_shell *env);

/*A function that checks if the cmd is a builtin*/
int		ft_is_builtin(t_token *token);

/*A function that prints the env vars*/
int		ft_env(t_list *env, int fdout);

/*A function that change the value of a variable in side the 2DArray env*/
int		ft_set_env(t_list *env, char *name, char *value);

/*A function that returns the position of a char in an an array of chars*/
/*Returns -1 if the char not found*/
int		ft_get_index(char *str, char c);

/*A function that counts how many chars in an array of chars*/
int		ft_count_char(char *str, char c);

/*A function that returns the path for a cmd*/
char	*ft_allocate_cmd(char **cmd, char **env);

/*A function that get the path either from the env:PATH or the backup*/
char	**ft_get_paths(char **env);

/*A function that matchthe path of a cmd joinning it with a '/'*/
char	*ft_match_path(char *command, char **paths_env);

int		ft_exec_function(t_token *token, int fdin, int fdout, t_shell *shell);

int		ft_or_function(t_token *token, int fdin, int fdout, t_shell *shell);

int		ft_and_function(t_token *token, int fdin, int fdout, t_shell *shell);

int		ft_priority_token(t_token *token, int fdin, int fdout, t_shell *shell);

int		ft_redir_token(t_token *token, int fi, int fo, t_shell *shell);

int		ft_pipe_token(t_token *token, int fdin, int fdout, t_shell *shell);

int		ft_execution_token(t_token *token, int fdin, int fdout, t_shell *shell);

char	*ft_remove_quotes(char *str);

int		ft_expand(t_token *token, t_shell *shell);

/*A function that checks if a directory exists or no*/
int		ft_dir_exists(char *pth, t_shell *shell);
/*RIDERICTIONS FUNCTION HERE*/
int		ft_redir_in_function(t_token *token);

int		ft_redir_out_function(t_token *token);

int		ft_redir_append_function(t_token *token);

int		ft_redir_heredoc_function(t_token *token);

void	ft_free(char **ptr);

void	ft_enable_echoctl(void);

void	ft_dup_pipes(int fdin, int fdout);

void	ft_increment_shellvl(t_shell *shell);

char	**ft_list_to_array(t_list *env);

int	ft_dir_exists(char *path, t_shell *shell);

int	ft_redir_heredoc_function(t_token *token);

#endif
