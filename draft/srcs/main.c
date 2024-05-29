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

t_token	*get_last_token(t_token *stash)
{
	if (stash == NULL)
		return (NULL);
	while (stash->next)
		stash = stash->next;
	return (stash);
}

t_cmds	*get_last_cmd(t_cmds *stash)
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
    t_token *last = get_last_token(*token_lst);
    if (last == NULL)
    {
        *token_lst = new_token;
    }
    else
    {
        last->next = new_token;
    }
}

int	get_arg_size(t_token **liste)
{
	int size;
	t_token *current = *liste;
	
	size = 0;
	while (current && current->token != PIPE)
	{
		size += ft_strlen(current->content);
		current = current->next;
	}
	return (size);
}

void	add_command(t_cmds **cmd_list, char *command, char *args)
{
	t_cmds *new_cmd = malloc(sizeof(t_cmds));
	if (new_cmd == NULL)
		return ;
	new_cmd->command = NULL;
	new_cmd->args = NULL;
	new_cmd->next = NULL;
	if (args != NULL)
		new_cmd->args = strdup(args);
	if (command != NULL)
		new_cmd->command = strdup(command);
	if (*cmd_list == NULL)
        	*cmd_list = new_cmd;
        else
        {
       		t_cmds *last = get_last_cmd(*cmd_list);
       		last->next = new_cmd;
       	}
}

t_cmds	*token_to_commands(t_token *token_list)
{
	t_cmds *cmd_list = NULL;
	t_token *current = token_list;
	char *cmd = NULL;
	char *args = NULL;
	int arg_size = 0;
	
	while (current)
	{
		while (current && current->token != STRING)
			current = current->next;
		if (current == NULL)
			break ;
		cmd = strdup(current->content);
		current = current->next;
		if (current)
		{
		arg_size = get_arg_size(&current);
		args = malloc(sizeof(char) * (arg_size + 1));
               	if (args == NULL)
               		return (NULL);
               	args[0] = '\0';
                while (current && current->token != PIPE)
		{
			args = ft_strjoin(args, current->content);
			current = current->next;
		}
		add_command(&cmd_list, cmd, args);
		free(args);
		cmd = NULL;
		arg_size = 0;
		}
		if (current)
			current = current->next;
	}
	return (cmd_list);
}

t_token_lex	get_symbol(char *symbol)	//check les diffrents symboles
{
	t_token_lex res;
	
	res = SYMBOL;
	if (symbol[0] == '-')
		res = DASH;
	if (symbol[0] == '\'')
		res = QUOTE;
	if (symbol[0] == '"')
		res = DOUBLEQUOTE;
	if (symbol[0] == '|')
		res = PIPE;
	if (symbol[0] == '<')
		res = L_ARROW;
	if (symbol[0] == '>')
		res = R_ARROW;
	return (res);
}

int	is_metachar(char c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (1);
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	if (c == '|')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

int	token_string(char *rl, t_token *new, int i)
{
	int	j;
	
	j = 0;
	while ((rl[i + j]) && (is_metachar(rl[i + j]) == 0))
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
int	check_arrow(char *rl, t_token *new, int i)
{
	if (new->token == L_ARROW && rl[i] == '<')
	{
		new->content = malloc(sizeof(char) * (3));
		if (!new->content)
		{
			free(new);
			return (0);
		}
		ft_strlcpy(new->content, rl + i - 1, 3);
		new->token = L_D_ARROW;
		return (1);
	}
	if (new->token == R_ARROW && rl[i] == '>')
	{
		new->content = malloc(sizeof(char) * (3));
		if (!new->content)
		{
			free(new);
			return (0);
		}
		ft_strlcpy(new->content, rl + i - 1, 3);
		new->token = R_D_ARROW;
		return (1);
	}
	return (0);
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
		if ((ft_isalpha(rl[i]) || ft_isdigit(rl[i])) || (is_metachar(rl[i]) == 0))
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
		if (new->token == L_ARROW || new->token == R_ARROW)
		{
			add = check_arrow(rl, new, i);
			i += add;
		}
		add_token(token_lst, new);
	}
}

char*	get_token_name(t_token_lex token) //pour print les tokens
{
	if (token == STRING)
		return "STRING";
	if (token == SYMBOL)
		return "SYMBOL";
	if (token == SPC)
		return "SPC";
	if (token == PIPE)
		return "PIPE";
	if (token == DOLLAR)
		return "DOLLAR";
	if (token == DASH)
		return "DASH";
	if (token == QUOTE)
		return "QUOTE";
	if (token == DOUBLEQUOTE)
		return "DOUBLEQUOTE";
	if (token == L_ARROW)
		return "L_ARROW";
	if (token == R_ARROW)
		return "R_ARROW";
	if (token == QUOTE_STRING)
		return "QUOTE_STRING";
	if (token == L_D_ARROW)
		return "L_D_ARROW";
	if (token == R_D_ARROW)
		return "R_D_ARROW";
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

/*int	check_newline(t_token *token_lst) // vrai (1) si -n
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
}*/

int	count_commands(t_cmds **cmd_lst)
{
	int i;
	t_cmds *current = *cmd_lst;
	
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
        }
        return (i); 
}

void	pipe_pipe(t_cmds **cmd_lst)
{
	int nbr_cmd;
	int	i;
	
	nbr_cmd = count_commands(cmd_lst);
	pid_t *pid = malloc(nbr_cmd * sizeof(pid_t));
	int (*fd)[2] = malloc((nbr_cmd) * sizeof(*fd));
	t_cmds *current_cmd = *cmd_lst;
	i = 0;
	while (i < nbr_cmd - 1)
	{
		if (pipe(fd[i]) == -1) 
			exit(-1);
		i++;
	}
	i = 0;
	while (current_cmd)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			exit (-1);
		else if (pid[i] == 0)
		{
			if (i > 0)
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
				close(fd[i - 1][0]);
			}
			if (i < nbr_cmd - 1)
			{
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][1]);
			}
			execute_command(current_cmd);
			exit(0);
		}
	i++;
	current_cmd = current_cmd->next;
	}
	i = 0;
	while (i < nbr_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i < nbr_cmd)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

void	echo(t_cmds *cmd_lst)
{
	int	new_line;
	int	i;
	
	i = 0;
	new_line = 0;
	while (cmd_lst->args[i] && cmd_lst->args[i] == ' ')
		i++;
	if (strncmp(cmd_lst->args + i, "-n", 2) == 0)
	{
		new_line = 1;
		i += 2;
	}
	while (cmd_lst->args[i] && cmd_lst->args[i] == ' ')
		i++;
	printf("%s", cmd_lst->args + i);
    	if (new_line == 0) // newline en fonction du booleen
    		printf("\n");
}	

void	execute_command(t_cmds *cmd_lst)
{
  	if (cmd_lst && cmd_lst->command != NULL && (strncmp(cmd_lst->command, "exit", 4) == 0))
	{
    		exit(1) ;
    	}
    	else if (cmd_lst && cmd_lst->command != NULL && (strncmp(cmd_lst->command, "echo", 5) == 0))
    		echo(cmd_lst);
}
        	
int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int	i;
	char	*rl;
	//DIR *mydir;
	//struct dirent *d;
	t_cmds *cmds = NULL;
	t_token *token_lst = NULL;
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
		rl = NULL;
		while (i < argc) //on utilisera stdinput et gnl pour mettre dans rl
		{
			rl = ft_strjoin(rl, argv[i]);
			i++;
		}
    		rl = readline("minishell > ");
    		token(rl, &token_lst);
    		cmds = token_to_commands(token_lst);
    		free(rl);
    		free_token_lst(token_lst);
    		token_lst = NULL;
    		if(cmds)
    		{
    			pipe_pipe(&cmds);
    			//exec_pipes(current);
        	}
    	//closedir(mydir);
    	}
    	return (0);
} // https://github.com/iciamyplant/Minishell/blob/master/tester/test.sh
