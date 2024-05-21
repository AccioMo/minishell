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

STAGE ONE:
	remove AND/OR tokens.
STAGE TWO:
	remove REDIR tokens.
STAGE THREE:
	remove PIPE tokens.
STAGE FOUR:
	parse WORD tokens or PARENTHESES.

ERROR HANDLING:
	1. error on if AND, OR, PIPE, and REDIRs tokens without a right or left token.
	2. error on unclosed SINGLE-QUOTES, DOUBLE-QUOTES or PARENTHESES.
	3. error on WORD token containing PARENTHESES or SUBSHELL containing WORD.


```

## EXECUTION
```c:

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
