/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/06/07 17:46:52 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <sys/time.h>
# include "libft.h"
# include "get_next_line.h"
# include "readline/readline.h"
# include "readline/history.h"

# define TRUE 1
# define FALSE 0
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define PARSING_FAILURE 258

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define S_OR "||"
# define S_AND "&&"
# define S_PIPE "|"
# define S_REDIR_IN "<"
# define S_REDIR_OUT ">"
# define S_REDIR_APPEND ">>"
# define S_REDIR_HEREDOC "<<"

int	g_signal;

typedef enum e_type
{
	REDIR_HEREDOC,
	REDIR_APPEND,
	REDIR_OUT,
	REDIR_IN,
	SUBSHELL,
	PIPE,
	WORD,
	AND,
	OR,
}	t_type;

typedef struct s_token
{
	struct s_token	*right;
	struct s_token	*left;
	t_type			type;
	char			**args;
}	t_token;

typedef struct s_shell
{
	t_token			*root;
	t_list			*env;
	struct termios	term;
	int				exit_code;
}	t_shell;

double	ft_gettimeofday(void);//huh??

int		ft_priority_token(t_token *token, int fdin, int fdout, t_shell *shell);

void	ft_free(char **ptr);

void	ft_toggle_cannonical_mode(void);

/*A function to grab any value of a key in a 2d array,e.g: Value of name User is loginDialk*/
/*Returns NULL if there is no key with that name*/
char	*ft_getenv(char *name, t_list *arr);

/*A function that return the size of a 2D array*/
int		ft_array_len(char **arr);

/*A function that copies a 2darray and return it*/
char	**copy_env(char **env);

char	**ft_append_to_array(char **args, char *new_arg);

/*A function  that realocate a 2d array with new dat for a 2d array double pointer*/
char	**ft_remove_from_array(char **array, int x);

int		ft_index(char *str, char c);

int		ft_whitespace(char c);

int		ft_perror(char *cmd);

void	ft_free_tree(t_token *token);

int		ft_found_token(char *str, char c);

int	ft_handle_wildecard(t_token *token, char *pattern);

int		ft_contains_variable(char *str);

void	ft_exit(t_shell *env);

#endif
