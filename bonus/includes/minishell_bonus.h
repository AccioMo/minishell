/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 02:14:36 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/07/18 11:20:14 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/time.h>
# include "libft.h"
# include "get_next_line.h"
# include "readline/readline.h"
# include "readline/history.h"

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
	char			**args;
	struct s_token	*right;
	struct s_token	*left;
	t_type			type;
	int				fd;
}	t_token;

typedef struct s_heredoc
{
	int					fd;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_shell
{
	t_token			*root;
	t_list			*env;
	int				subshell;
	pid_t			last_pid;
	int				exit_code;
}	t_shell;

int		ft_priority_token(t_token *token, int fdin, int fdout, t_shell *shell);
void	ft_free(char **ptr);
char	*ft_realloc(char *line, char *buffer);
char	*ft_getenv(char *name, t_list *arr);
int		ft_expand_heredoc(t_token *token, t_shell *shell);
int		ft_array_len(char **arr);
char	**ft_append_to_array(char **args, char *new_arg);
char	*ft_quoted_variables(char *str, t_shell *shell);
char	*ft_expand_variable(char *str, t_shell *shell);
char	*ft_heredoc_variables(char *str, t_shell *shell);
int		ft_variable_length(char *str);
int		set_exit_code(int exit_code, int set);
void	ft_reset_term(void);
char	**ft_remove_from_array(char **array, int x);
int		ft_index(char *str, char c);
void	ft_increment_shellvl(t_shell *shell);
int		ft_whitespace(char c);
int		ft_perror(char *cmd, int code);
void	ft_free_tree(t_token *token);
int		ft_found_token(char *str, char c);
int		ft_set_env(t_shell *shell, char *name, char *value);
int		ft_redir_heredoc_function(t_token *token, t_shell *shell);
int		ft_contains_variable(char *str);
int		ft_exit(t_token *token, t_shell *env);
void	main_sig_handler(int signal);
void	sort_arr(char **oldbuff);

#endif
