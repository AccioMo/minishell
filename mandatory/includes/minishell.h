/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/06 16:51:07 by mzeggaf          ###   ########.fr       */
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
# define PIPE_READ 3

typedef enum e_type
{
	REDIR_IN,
	REDIR_OUT,
	WORD,
	PIPE,
	AND,
	OR,
}	t_type;

typedef int	t_io;

typedef struct s_token
{
	struct s_token	*right;
	struct s_token	*left;
	t_type			type;
	t_io			input;
	t_io			output;
	char			**args;
}	t_token;

typedef struct s_env
{
	char	**env;
	char	**vars;
	t_token	*root;
}	t_env;

#endif
