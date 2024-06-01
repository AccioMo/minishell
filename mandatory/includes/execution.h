/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/01 16:45:14 by mzeggaf          ###   ########.fr       */
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

/*The exit function that ends the proccess of minishell*/
void	ft_exit(t_token *token, t_shell *env);

/*A function that prints the env vars*/
int		ft_env(t_list *env, int fdout);

/*A function that reallocate a 2D array with a new subArray or Overwrite the existing one*/
/*Returns NULL if Malloc Failed*/
char	**ft_realloc_env(char **env, int size, char *new_var);

/*A function that change the value of a variable in side the 2DArray env*/
int		ft_change_env_value(t_list *env, char *name, char *value);

/*Q function that do what strjoin do but it free the first param if the code is equal to or smaller than 2 or free the second param if the code is bigger than or equal to 2 or both if code == 2*/
char	*ft_strjoin_free(char *s1, char *s2, int code);

/*A function that returns the position of a char in an an array of chars*/
/*Returns -1 if the char not found*/
int 	ft_get_index(char *str, char c);

/*A function that counts how many chars in an array of chars*/
int		ft_count_char(char *str, char c);

/*A function that returns the path for a cmd*/
char	*ft_allocate_cmd(char **cmd, char **env);

/*A function that get the path either from the env:PATH or the backup*/
char	**ft_get_paths(char **env);

/*A function that matchthe path of a cmd joinning it with a '/'*/
char	*ft_match_path(char *command, char **paths_env);

int	ft_exec_function(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_or_function(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_and_function(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_priority_token(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_redirections_token(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_pipe_token(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_execution_token(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_pipe_function(t_token *token, int fdin, t_shell *shell);

/*A function that expand variables to there values from the env*/
int	ft_variables(t_token *token, t_shell *shell);

/*A function that changes the '*' to a dir content*/
int	ft_wildcard(t_token *token);

char	*ft_remove_quotes(char *str);

int	ft_expand(t_token *token, t_shell *shell);

/*A function that checks if a directory exists or no*/
int ft_dir_exists(char *pth, t_shell *shell);
/*RIDERICTIONS FUNCTION HERE*/
int	ft_redir_in_function(t_token *token);

int	ft_redir_out_function(t_token *token);

int	ft_redir_append_function(t_token *token);

int	ft_redir_heredoc_function(t_token *token);

void	ft_free(char **ptr);
#endif
