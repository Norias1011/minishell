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

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *rl;
	int	i;
	DIR *mydir;
	struct dirent *d;
	struct stat mystat;
	char buf[512];
	const char *dir_path = "/home/brh/Bureau/minishell/minishell";
	
	mydir = opendir(dir_path);
	if (mydir == NULL)
	{
		perror("opendir");
		return 1;
	}
	while (1)
	{
	i = 1;
	while (i < argc)
	{
		rl = ft_strjoin(rl, argv[i]);
		i++;
	}
    	rl = readline("minishell > ");
    	if (rl[0] == 'l' && rl[1] == 's' && rl[2] == '\0')
	{
            	while ((d = readdir(mydir)) != NULL)
               	 	printf("%s\n", d->d_name);
        }
        else
    		printf("%s\n", rl);
    	}
    	closedir(mydir);
    	return (0);
}
