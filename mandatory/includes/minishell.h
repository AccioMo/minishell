/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/05/03 16:09:24 by mzeggaf          ###   ########.fr       */
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

#define true 1
#define false 0
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define SUCCESS 1
#define ERROR 0

typedef struct s_cmds {
	char	**cmd;
	char	*infile;
	char	*outfile;
	int		fd_in;
	int		fd_out;
	int		operato;
	int		pipe[2];
	struct s_cmds	*next;
} t_cmds;

#endif
