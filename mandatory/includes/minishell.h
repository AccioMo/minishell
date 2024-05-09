/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/09 23:42:27 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define ERROR 0

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
	PIPE,
	WORD,
	AND,
	OR,
}	t_type;

typedef struct t_io
{
	int		fdin;
	int		fdout;
	char	*infile;
	char	*outfile;
	t_iot	type;
}	t_io;

typedef struct s_token
{
	struct s_token	*right;
	struct s_token	*left;
	t_type			type;
	t_io			io;
	char			**args;
}	t_token;

typedef struct s_shell
{
	char	**env;
	char	**vars;
	t_token	*root;
}	t_shell;

#endif
