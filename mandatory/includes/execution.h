/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/19 10:53:33 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <termios.h>

/*A mimit of echo function with -n option only*/
int		ft_echo(t_token	*token, int fdout);

/*A mimit of pwd function*/
int		ft_pwd(int fdout);

/*A mimit function of cd*/
int		ft_cd(t_token *token, t_shell *env);

/*A mimit function of unset shell-builtin functions*/
int		ft_unset(t_token *token, t_shell *env);

/*A function that return the size of a 2D array*/
int		ft_two_d_len(char **arr);

/*A mimit function of export shell-builtin functions*/
int		ft_export(t_token *cmd, t_shell *env, int fdout);

/*A function that execute builtin functions*/
int		ft_execute_builtin(t_token *cmd,int fdout, t_shell *env);

/*A function that checks if the cmd is a builtin*/
int		ft_have_builtin(t_token *token);

/*The exit function that ends the proccess of minishell*/
void	ft_exit(t_token *token, t_shell *env);

void	ft_exec_cmd(char *full_cmd, char **env, int cmd_in, int *fd_pipe);

/*A function that prints the env vars*/
int	ft_env(t_shell *shell, int fdout);

/*A function to grab any value of a key in a 2d array,e.g: Value of name User is loginDialk*/
/*Returns NULL if there is no key with that name*/
char	*ft_getenv(char *name, char **arr);

/*A function that reallocate a 2D array with a new subArray or Overwrite the existing one*/
/*Returns NULL if Malloc Failed*/
char	**ft_realloc_env(char **env, int size, char *new_var);

int	ft_exec_function(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_or_function(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_and_function(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_define_priority(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_check_redirections(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_check_pipe(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_type_to_execute(t_token *token, int fdin, int fdout, t_shell *shell);

int	ft_pipe_function(t_token *token, int fdin, t_shell *shell);

/*RIDERICTIONS FUNCTION HERE*/
int	ft_redir_in_function(t_token *token);

int	ft_redir_out_function(t_token *token);

int	ft_redir_append_function(t_token *token);

int	ft_redir_heredoc_function(t_token *token);

void	ft_free(char **ptr);
#endif
