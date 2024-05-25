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

t_list	*get_last(t_list *stash)
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

void add_token(t_list **token_lst, t_list *new_token)
{
    t_list *last = get_last(*token_lst);
    if (last == NULL)
    {
        *token_lst = new_token;
    }
    else
    {
        last->next = new_token;
    }
}

void token(char *rl, t_list **token_lst)
{
    int i = 0;
    int j;
    while (rl[i])
    {
        t_list *new = malloc(sizeof(t_list));
        if (!new)
            return;

        new->content = malloc(sizeof(char) * (ft_strlen(rl) + 1));
        if (!new->content)
        {
            free(new);
            return;
        }

        j = 0;
        if (ft_isdigit(rl[i]))
        {
            while (ft_isdigit(rl[i + j]))
                j++;
            ft_strlcpy(new->content, rl + i, j + 1);
            new->content[j + 2] = '\0';
            new->token = NUMBER;
        }
        else if (ft_isalpha(rl[i]))
        {
            while (ft_isalpha(rl[i + j]))
                j++;
            ft_strlcpy(new->content, rl + i, j + 1);
            new->content[j + 2] = '\0';
            new->token = STRING;
        }
        else if (rl[i] == ' ')
        {
            while (rl[i + j] == ' ')
                j++;
            ft_strlcpy(new->content, rl + i, j + 1);
            new->content[j + 2] = '\0';
            new->token = SPC;
        }
        else
        {
            while (rl[i + j] && !(rl[i + j] == ' ') && !ft_isalpha(rl[i + j]) && !ft_isdigit(rl[i + j]))
                j++;
            ft_strlcpy(new->content, rl + i, j + 1);
            new->content[j + 2] = '\0';
            new->token = SYMBOL;
        }
        
        new->next = NULL;
        add_token(token_lst, new);
        i += j;
    }
}

        	
int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int	i;
	char	*rl;
	DIR *mydir;
	//struct dirent *d;
	t_list	*token_lst;
	const char *dir_path = "/home/brh/Bureau/minishell";
	
	token_lst = NULL;
	rl = NULL;
	mydir = opendir(dir_path);
	if (mydir == NULL)
	{
		perror("opendir");
		return 1;
	}
	while (1)
	{
	mydir = opendir(dir_path);
	i = 1;
	while (i < argc)
	{
		rl = ft_strjoin(rl, argv[i]);
		i++;
	}
    	rl = readline("minishell > ");
    	token(rl, &token_lst);
    	t_list *current = token_lst;
        while (current)
        {
            if (current->token == NUMBER)
                printf("NUMBER");
            else if (current->token == SPC)
                printf("SPC");
            else if (current->token == SYMBOL)
                printf("SYMBOL");
            else if (current->token == STRING)
                printf("STRING");
            printf(" ->  %s", current->content);
            printf(" / ");
            t_list *temp = current;
            current = current->next;
            free(temp->content);
            free(temp);
        }
        token_lst = NULL;
        free(rl);
        printf("\n");
    	/*if (ft_strncmp(rl, "ls", 2) == 0)
	{
            	while ((d = readdir(mydir)) != NULL)
               	 	printf("%s\n", d->d_name);
        }
        else
    		printf("%s\n", rl);
    	closedir(mydir);*/
    	}
    	return (0);
}
