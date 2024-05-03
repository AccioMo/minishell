#include <errno.h>
#include <execution.h>

void	ft_free(char **ptr)
{
	char	**hold;

	hold = ptr;
	if (!ptr)
		return ;
	while (*ptr)
		free(*ptr++);
	free(hold);
}

static void	ft_perror(char **cmd)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd(*cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd(*cmd, 2);
		ft_putstr_fd(": permission denied\n", 2);
	}
	else
		perror(*cmd);
}

char	**ft_get_paths(char **env)
{
	if (!*env)
		return (ft_split("/goinfre/mzeggaf/.brew/bin:/usr/local/bin:\
		/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:\
		/goinfre/mzeggaf/.brew/bin:/Users/mzeggaf/Desktop/nodejs/bin", ':'));
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH", 4))
			return (ft_split((*env) + 5, ':'));
		env++;
	}
	return (NULL);
}

char	*ft_cmd_cpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (*src == '\\' && *(src + 1))
			src++;
		else if (*src == '\'' || *src == '\"')
		{
			src++;
			if (*(src - 1) == '\'')
				while (*src && *src != '\'')
					*(dst + i++) = *src++;
			else if (*(src - 1) == '\"')
				while (*src && *src != '\"')
					*(dst + i++) = *src++;
		}
		else
			*(dst + i++) = *src++;
	}
	*(dst + i) = '\0';
	return (dst);
}

char	*ft_match_path(char *command, char **paths_env)
{
	char	*command_path;
	char	*tmp_path;

	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
		return (perror(command), NULL);
	}
	while (*paths_env)
	{
		tmp_path = ft_strjoin(*paths_env, "/");
		command_path = ft_strjoin(tmp_path, command);
		free(tmp_path);
		if (!command_path)
			return (NULL);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
		paths_env++;
	}
	return (ft_strdup(""));
}

void	ft_dup_pipes(int cmd_in, int *fd_pipe)
{
	if (dup2(cmd_in, 0) < 0 || dup2(fd_pipe[1], 1) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(cmd_in);
		close(fd_pipe[1]);
		close(fd_pipe[0]);
	}
}

char	*ft_allocate_cmd(char **cmd, char **env)
{
	char	**paths_env;
	char	*cmd_path;

	paths_env = ft_get_paths(env);
	if (!paths_env)
	{
		ft_free(cmd);
		return (NULL);
	}
	cmd_path = ft_match_path(*cmd, paths_env);
	ft_free(paths_env);
	if (!cmd_path)
	{
		ft_free(cmd);
		return (NULL);
	}
	return (cmd_path);
}

void	ft_exec_cmd(char **cmd, char **env, int cmd_in, int *fd_pipe)
{
	char	*cmd_path;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		if (cmd_in < 0)
			exit(EXIT_FAILURE);
		ft_dup_pipes(cmd_in, fd_pipe);
		if (!cmd)
			exit(EXIT_FAILURE);
		cmd_path = ft_allocate_cmd(cmd, env);
		if (!cmd_path)
			exit(EXIT_FAILURE);
		execve(cmd_path, cmd, env);
		ft_perror(cmd);
		free(cmd_path);
		ft_free(cmd);
		exit(1);
	}
	else if (pid < 0)
		perror("fork");
}