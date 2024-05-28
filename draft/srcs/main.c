/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:11:46 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/23 17:12:54 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_token	*get_last(t_token *stash)
{
	if (stash == NULL)
		return (NULL);
	while (stash->next)
		stash = stash->next;
	return (stash);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		j;

	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	j = ft_strlen(s1) + ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (j + 1));
	if (res == NULL)
		return (NULL);
	j = 0;
	while (s1[j])
	{
		res[j] = s1[j];
		j++;
	}
	j = 0;
	while (s2[j])
	{
		res[ft_strlen(s1) + j] = s2[j];
		j++;
	}
	res[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (res);
}

void	add_token(t_token **token_lst, t_token *new_token)
{
    t_token *last = get_last(*token_lst);
    if (last == NULL)
    {
        *token_lst = new_token;
    }
    else
    {
        last->next = new_token;
    }
}

t_token_lex	get_symbol(char *symbol)	//check les diffrents symboles
{
	t_token_lex res;
	
	res = SYMBOL;
	if (symbol[0] == '+')
		res = ADD;
	if (symbol[0] == '-')
		res = SOUSTRACT;
	if (symbol[0] == '*')
		res = MULTI;
	if (symbol[0] == '/')
		res = SLASH;
	if (symbol[0] == '\\')
		res = BACKSLASH;
	if (symbol[0] == ',')
		res = COMA;
	if (symbol[0] == '.')
		res = DOT;
	if (symbol[0] == '-')
		res = DASH;
	if (symbol[0] == '\'')
		res = QUOTE;
	if (symbol[0] == '"')
		res = DOUBLEQUOTE;
	if (symbol[0] == '_')
		res = UNDERSCORE;
	if (symbol[0] == '|')
		res = PIPE;
	if (symbol[0] == '=')
		res = EQUAL;
	if (symbol[0] == ';')
		res = SEMICOLON;
	if (symbol[0] == '<')
		res = LEFT_ARROW;
	if (symbol[0] == '>')
		res = RIGHT_ARROW;
	return (res);
}

int	is_metachar(char c)
{
	if (c == '\'')
		return (1);
	if (c <= 13 && c >= 11)
		return (1);
	if (c == '"')
		return (1);
	if (c == '&')
		return (1);
	if (c == ';')
		return (1);
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	if (c == '(')
		return (1);
	if (c == ')')
		return (1);
	if (c == '$')
		return (1);
	if (c == ' ')
		return (1);
	if (c == '\\')
		return (1);
	return (0);
}

int	token_digit(char *rl, t_token *new, int i)
{
	int	j;
	
	j = 0;
	while (ft_isdigit(rl[i + j]))
		j++;
	new->content = malloc(sizeof(char) * (j + 1));
	if (!new->content)
	{
		free(new);
		return (0);
	}
	ft_strlcpy(new->content, rl + i, j + 1);
	new->token = NUMBER;
	return (j);
}

int	token_string(char *rl, t_token *new, int i)
{
	int	j;
	
	j = 0;
	while (ft_isalpha(rl[i + j]))
		j++;
	new->content = malloc(sizeof(char) * (j + 1));
	if (!new->content)
	{
		free(new);
		return (0);
	}
	ft_strlcpy(new->content, rl + i, j + 1);
	new->token = STRING;
	return (j);
}

int	token_space(char *rl, t_token *new, int i)
{
	int	j;
	
	j = 0;
	while (rl[i + j] == ' ')
		j++;
	new->content = malloc(sizeof(char) * (j + 1));
	if (!new->content)
	{
		free(new);
		return (0);
	}
	ft_strlcpy(new->content, rl + i, j + 1);
	new->token = SPC;
	return (j);
}

int	token_symbol(char *rl, t_token *new, int i)
{	
	int	j;
	
	j = 1;
	new->content = malloc(sizeof(char) * (j + 1));
	if (!new->content)
	{
		free(new);
		return (0);
	}
	ft_strlcpy(new->content, rl + i, j + 1);
	new->token = get_symbol(new->content);
	return (j);
}

//void	single_or_double_quote(char *rl, t_token **token_lst, int i);

int	quote_handler(char *rl, t_token *new, int i)
{
	int	j;
	int	is_dollar;
	
	j = 0;
	is_dollar = 0;
	while (rl[i + j] && rl[i + j] != rl[i - 1])
	{
		if (rl[i + j] == '$' && rl[i - 1] == '"')
			is_dollar = 1;
		j++;
	}
	if (i + j == ft_strlen(rl) && rl[i + j] != rl[i - 1]) //&& j != 0)
		return (-1);
	new->content = malloc(sizeof(char) * (j + 1));
	if (!new->content)
	{
		free(new);
		return (0);
	}
	if (j == 0 && rl[i] != ft_strlen(rl))
	{
		ft_strlcpy(new->content, " ", j + 1);
		new->token = SPC;
	}
	else
	{
		ft_strlcpy(new->content, rl + i, j + 1);
		new->token = QUOTE_STRING;
		if (is_dollar == 1)
			new->token = STRING;
	}
	return (j);
}

void	token(char *rl, t_token **token_lst)
{
	int	i;
	int	add;
	t_token *new;
	
	i = 0;
	add = 0;
	while (rl[i])
	{
		new = malloc(sizeof(t_token));
		if (!new)
			return ;
		if (ft_isdigit(rl[i])) 
			add = token_digit(rl, new, i);
		else if (ft_isalpha(rl[i]))
			add = token_string(rl, new, i);
		else if (rl[i] == ' ')
			add = token_space(rl, new, i);
		else
			add = token_symbol(rl, new, i);
		new->next = NULL;
		i += add;
		if ((new->token == QUOTE || new->token == DOUBLEQUOTE))
		{
			add = quote_handler(rl, new, i);
			if (add != -1)
			{
				i += add + 1;
				add_token(token_lst, new);
			}
			else
				add_token(token_lst, new);
			continue ;
		}	
		add_token(token_lst, new);
	}
}

char*	get_token_name(t_token_lex token) //pour print les tokens
{
	if (token == NUMBER)
		return "NUMBER";
	if (token == STRING)
		return "STRING";
	if (token == SYMBOL)
		return "SYMBOL";
	if (token == SPC)
		return "SPC";
	if (token == PIPE)
		return "PIPE";
	if (token == ADD)
		return "ADD";
	if (token == SOUSTRACT)
		return "SOUSTRACT";
	if (token == MULTI)
		return "MULTI";
	if (token == DOLLAR)
		return "DOLLAR";
	if (token == SLASH)
		return "SLASH";
	if (token == BACKSLASH)
		return "BACKSLASH";
	if (token == COMA)
		return "COMA";
	if (token == DOT)
		return "DOT";
	if (token == DASH)
		return "DASH";
	if (token == QUOTE)
		return "QUOTE";
	if (token == DOUBLEQUOTE)
		return "DOUBLEQUOTE";
	if (token == UNDERSCORE)
		return "UNDERSCORE";
	if (token == EQUAL)
		return "EQUAL";
	if (token == SEMICOLON)
		return "SEMICOLON";
	if (token == LEFT_ARROW)
		return "LEFT_ARROW";
	if (token == RIGHT_ARROW)
		return "RIGHT_ARROW";
	if (token == QUOTE_STRING)
		return "QUOTE_STRING";
	return "UNKNOW";
}


void	free_token_lst(t_token *token_lst)
{
	while (token_lst)
	{
		t_token *temp = token_lst;
		token_lst = token_lst->next;
		free(temp->content);
		free(temp);
	}
}

int	check_newline(t_token *token_lst) // vrai (1) si -n
{
	int	i;
	
	i = 0;
	if ((token_lst) && (token_lst->token == DASH) && (token_lst->next) && (strncmp((token_lst->next)->content, "n", 1) == 0))
	{
		while (i < ft_strlen(token_lst->next->content)) // gere echo -nnnn test
		{
			if (token_lst->next->content[i] != 'n')
				return (0);
			i++;
		}
		if (!token_lst->next->next)
			return (1);
		if ((token_lst->next->next->token == SPC || token_lst->next->next->token == PIPE))
			return (1);
	}
	return (0);
}

t_token	*echo(t_token *current)
{
	int	new_line;
	
	new_line = 0;
	current = current->next;
    	if (current && current->token == SPC)
    		current = current->next;
    	while (check_newline(current) == 1) //check s'il y a plusieurs -n a la suite et les passes fout newline à 1 (bool)
    	{
    		current = current->next;
    		current = current->next;
    		if (current && current->token == SPC)
    			current = current->next;
    		new_line = 1;
    	}
    	while (current && current->token != PIPE) //&& !(strncmp(current->content, "\\n", 3) == 0)) //ecris le reste
    	{
    		if (current->token == SPC && ft_strlen(current->content) > 1)
    		{
    			printf("%c", ' ');
    			current = current->next;
    		}
    		else
    		{
    			printf("%s", current->content);	
    			current = current->next;
    		}
    	}
    	if (new_line == 0) // newline en fonction du booleen
    		printf("\n");
    	return (current);
}	

t_token	*check_command(t_token *current) // test command de base avec le premier string
{
	//t_token *current = token_lst;
	int	check;
	
	check = 0;
	while (current && current->token == SPC) //|| strncmp(current->content, "\\n", 3) == 0))
    		current = current->next;
	if (current && (strncmp(current->content, "exit", 4) == 0) && !(current->next))
	{
    		free_token_lst(current);
    		exit(1) ;
    	}
    	if (current && (strncmp(current->content, "echo", 5) == 0))
    	{
    		current = echo(current);
    		check = 1;
    	}
    	/*if ((ft_strncmp(rl, "ls", 2) == 0) && (current->next) && current->next->token == SPC)
    	{
		while ((d = readdir(mydir)) != NULL)
			printf("%s\n", d->d_name);     // fonction pour ls
               	return (1);
        }*/
        if (current && current->token == PIPE)
        	current = current->next;
        if (current && check == 1)
        	current = check_command(current);
    	return (current);
}
        	
int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int	i;
	char	*rl;
	//DIR *mydir;
	//struct dirent *d;
	t_token	*token_lst;
	//const char *dir_path = "/home/brh/Bureau/minishell"; //mettre ton path si tu veux tester
	
	token_lst = NULL;
	rl = NULL;
	/*mydir = opendir(dir_path); 
	if (mydir == NULL) // fonction ls check path valide
	{
		perror("opendir");
		return 1;
	}*/
	while (1)
	{
	//mydir = opendir(dir_path);
		i = 1;
		while (i < argc) //on utilisera stdinput et gnl pour mettre dans rl
		{
			rl = ft_strjoin(rl, argv[i]);
			i++;
		}
    		rl = readline("minishell > ");
    		token(rl, &token_lst);
    		free(rl);
    		t_token *current = token_lst;
    		if(current)
    		{
    			while (token_lst->token == SPC && token_lst->next)
    				token_lst = token_lst->next;
    			current = check_command(current);
    			while (current)
        		{
        			printf(" %s ->  %s", get_token_name(current->token), current->content);
        			printf("\n");
        			current = current->next;
        		}
        		free_token_lst(token_lst);
        		token_lst = NULL;
        	}
    	//closedir(mydir);
    	}
    	return (0);
} // https://github.com/iciamyplant/Minishell/blob/master/tester/test.sh
