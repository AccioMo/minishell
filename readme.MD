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

```
int recursive_function(token)
{
	if token->left->type == WORD {
		execution_function(token)
	}
	else {
		recursive_function(token->left)
		recursive_function(token->right)
	}
}

int execution_function(token)
{
	if token->type == REDIR_IN {
		redir_in_function(token, env)
	}
	else if token->type == REDIR_OUT {
		redir_out_function(token, env)
	}
	else if token->type == PIPE {
		pipex_function(token, env) // read end of pipe is out
	}
	else if token->type == AND {
		and_function(token, env)
	}
	else if token->type == OR {
		or_function(token, env)
	}
}
```
every token tells its right child 