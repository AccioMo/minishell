/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/22 00:01:34 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <errno.h>
# include <signal.h>
# include "readline/readline.h"
# include "readline/history.h"

# define TRUE 1
# define FALSE 0
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

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

typedef enum e_iot
{
	READ,
	WRITE,
	APPEND,
	HEREDOC,
}	t_iot;

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
	char	**env;
	int		exit_status;
	t_token	*root;
}	t_shell;

int		ft_define_priority(t_token *token, int fdin, int fdout, t_shell *shell);
void	ft_free(char **ptr);

/*A function to grab any value of a key in a 2d array,e.g: Value of name User is loginDialk*/
/*Returns NULL if there is no key with that name*/
char	*ft_getenv(char *name, char **arr);

/*A function that return the size of a 2D array*/
int		ft_two_d_len(char **arr);

/*A function that copies a 2darray and return it*/
char	**copy_env(char **env);

int		ft_index(char *str, char c);

void	ft_free_tree(t_token *token);
#endif
