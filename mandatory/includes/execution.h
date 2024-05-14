/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/04 16:02:46 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <termios.h>

/*A mimit of echo function with -n option only*/
int		ft_echo(t_token	*token);

/*A mimit of pwd function*/
int		ft_pwd(t_env *env);

/*A mimit function of cd*/
int		ft_cd(t_token *token, t_env *env);

/*A mimit function of unset shell-builtin functions*/
int		ft_unset(t_token *token, t_env *env);

/*A function that return the size of a 2D array*/
int		ft_two_d_len(char **arr);

/*The main execution function that checks where the token needs to be executed, Returns the exit status of theat cmd*/
int		ft_execute(t_token *cmd, t_env *env);

/*A mimit function of export shell-builtin functions*/
int		ft_export(t_token *cmd, t_env *env);

/*A function that execute builtin functions*/
int		ft_execute_builtin(t_token *cmd, t_env *env);

/*A function that checks if the cmd is a builtin*/
int		ft_have_builtin(t_token *token);

/*The exit function that ends the proccess of minishell*/
void	ft_exit(t_token *token, t_env *env);

void	ft_exec_cmd(char *full_cmd, char **env, int cmd_in, int *fd_pipe);

/*A function to grab any value of a key in a 2d array,e.g: Value of name User is loginDialk*/
/*Returns NULL if there is no key with that name*/
char	*ft_getenv(char *name, char **arr);

/*A function that reallocate a 2D array with a new subArray or Overwrite the existing one*/
/*Returns NULL if Malloc Failed*/
char	**ft_realloc_env(char **env, int size, char *new_var);

/*A function that free the token struct*/
void	ft_free_token(t_token *token);

/*A function that free the env struct*/
void	ft_free_env(t_env *env);


#endif
