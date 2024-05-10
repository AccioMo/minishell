### Token struct:
```c:
	typedef struct s_token
	{
		t_token	*right;
		t_token	*left;
		t_type	type;
		t_io	input;
		t_io	output;
		char	**args;
	}	t_token;
```

## PARSING
```
ft_add_token()
ft_and_or_split() // STAGE ONE: recursive
ft_pipe_split() // STAGE TWO: recursive
ft_redir_split() // STAGE THREE: not recursive (probably)
```

## EXECUTION
```

int stage_one_function(token)
{
	if token->type == AND {
		return (and_function(token, env))
	}
	else if token->type == OR {
		return (or_function(token, env))
	}
	return (stage_two_function(token))
}

int stage_two_function(token)
{
	if token->type == PIPE {
		pipe_function(token, env)
	}
	else if token->type == WORD {
		exec_function(token, env)
	}
	else if token->type == REDIR_IN {
		redir_function(token, env)
	}
	else if token->type == REDIR_OUT {
		redir_function(token, env)
	}
	else if token->type == SUBSHELL {
		recursive_function(token->left, env)
	}
}

int	and_function()
{
	if (recursive_function(token->left)) {
		recursive_function(token->right)
	} else {
		return 0;
	}
}

int	or_function()
{
	if (!recursive_function(token->left)) {
		recursive_function(token->right)
	} else {
		return 0;
	}
}

int	pipe_function(token, fdin, fdout)
{
	int fd = exec_function(token->left, fdin, fdout)
	if (token->right->type == PIPE)
		pipe_function(token->right, fd, )
	else if (token->right->type == WORD)
		exec_function(token->left, fd, 1)
	else if (token->right->type == SUBSHELL)
		recursive_function(token->left, env)
}
```
every token tells its right child
