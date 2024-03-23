/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/03/23 14:45:18 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

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
	int		operator;
	int		pipe[2];
	struct s_cmds	*next;
} t_cmds;

int		ft_echo(t_cmds	*cmds);
int		ft_pwd(void);
int		ft_pipex(char **cmds, char **env);
void	ft_exec_cmd(char *full_cmd, char **env, int cmd_in, int *fd_pipe);

#endif
