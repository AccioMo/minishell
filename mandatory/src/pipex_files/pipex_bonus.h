/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 00:38:40 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/02/25 16:35:35 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define BUFFER_SIZE 1024

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "../../libft/libft.h"
# include "../../get_next_line/get_next_line.h"

/* Checks number of arguments passed to the program. Exits if `argc < 5`. */
void	ft_input_check(int argc, char **argv);

/* Takes in a null-terminated array of `cmds`, executes each in new */
/* execve(2) process, and outputs to file with same name as last element */
/* of the array. Returns `1` or `0`.*/
int		ft_pipex(char **cmds, char **paths_env);

/* Free a null-terminated array. */
void	ft_free(char **ptr);

/* Takes in a null-terminated array of `args`, replicates `here_document` */
/* behavior with `args[0]` as LIMITER, then executes each in new execve(2) */
/* process, and outputs to file with same name as last element */
/* of the array. Returns `1` or `0`.*/
int		ft_here_doc(char **args, char **paths_env);

/* Returns `PATH` environment variable.*/
char	**ft_get_paths(char **env);

/* Matches `command` with its binary executable. Returns path on success, */
/* `NULL` on failure. */
char	*ft_match_path(char *command, char **paths_env);

/* Copies command from `src` to `dst`. */
char	*ft_cmd_cpy(char *dst, char *src, int len);

/* Splits command with its arguments into `execve(2)` compatible string.*/
char	**ft_cmd_split(char *str, char c);

/* Executes `cmd` in new process. Reads from `fdin` and writes to `fdout`.*/
void	ft_exec_cmd(char *str_cmd, char **paths_env, int fdin, int *fd_pipe);

#endif
