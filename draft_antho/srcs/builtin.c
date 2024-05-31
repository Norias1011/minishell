/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:53:37 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/31 23:52:50 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo(t_cmds *cmd_lst)
{
	int new_line;
	int i;

	i = 0;
	new_line = 1;
	if (cmd_lst->args == NULL)
	// fix echo avec ça mais bon bof quoi est ce que args null = il peut meme pas check args[0] = '\0' ?
	{
		printf("\n");
		return ;
	}
	while (cmd_lst->args[i] != '\0' && cmd_lst->args[i] == ' ')
		// passe les premiers espace
		i++;
	if (cmd_lst->args[i] != '\0' && (strncmp(cmd_lst->args + i, "-n", 2) == 0)
		&&
		((cmd_lst->args[i + 2] == ' ') || cmd_lst->args[i + 2] == '\0' ||
			(cmd_lst->args[i + 2] == 'n'))) /* check -n avec possibilite
																																																																																																																																																																																																																																															-nnnnnnnn...*/
	{
		i += 2;
		new_line = 0;
		while (cmd_lst->args[i] != '\0' && cmd_lst->args[i] == 'n')
			i++;
	}
	while (cmd_lst->args[i] != '\0' && cmd_lst->args[i] == ' ')
		// vire les espace pour le -n
		i++;
	while (cmd_lst->args[i] != '\0') // tant que y a des trucs a ecrire
	{
		while (cmd_lst->args[i] == ' ' && (cmd_lst->args[i + 1] == ' '
				|| cmd_lst->args[i + 1] == '\0'))
			// vire les espaces entre les mots en en gardant 1
			i++;
		if (cmd_lst->args[i] != '\0') // print
			printf("%c", cmd_lst->args[i]);
		i++;
	}
	if (new_line == 1) // newline en fonction du booleen
		printf("\n");
}

void	pwd(t_minishell *minishell, t_cmds *cmd_lst)
{
	char	*pwd;

	(void)cmd_lst;
	pwd = get_env_value(minishell, "PWD");
	if (pwd == NULL)
	{
		printf("Error: get_env_value failed\n");
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
}

void	env_built(t_minishell *minishell, t_cmds *cmd_lst)
{
	t_env	*tmp;

	(void)cmd_lst;
	tmp = minishell->env_s;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	cd_built(t_minishell *minishell, t_cmds *cmd_lst)
{
	char	*path;
	char	*pwd;

	printf("cd called\n");
	if (cmd_lst->args == NULL)
	{
		cd_home(minishell);
		return ;
	}
	else
		path = cmd_lst->args;
	if (chdir(path) == -1)
	{
		perror("cd");
		return ;
	}
	set_env_value(minishell, "OLDPWD", get_env_value(minishell, "PWD"));
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		printf("Error: getcwd failed\n");
		return ;
	}
	set_env_value(minishell, "PWD", pwd);
	return ;
}

int	cd_home(t_minishell *minishell)
{
	char	*home;
	char	*old;

	printf("BEFORE PWD: %s\n", get_env_value(minishell, "PWD"));
	printf("BEFORE OLDPWD: %s\n", get_env_value(minishell, "OLDPWD"));
	//set_env_value(minishell, "OLDPWD", get_env_value(minishell, "PWD"));
	old = get_env_value(minishell, "PWD");
	home = get_env_value(minishell, "HOME");
	if (home == NULL)
	{
		printf("Error: get_env_value failed\n");
		return (0);
	}
	if (chdir(home) != -1)
	{
		set_env_value(minishell, "OLDPWD", old);
		set_env_value(minishell, "PWD", home);
		printf("AFTER PWD: %s\n", get_env_value(minishell, "PWD"));
		printf("AFTER OLDPWD: %s\n", get_env_value(minishell, "OLDPWD"));
		return (0);
	}
	return (1);
}

/*int	oldpwd_built(t_minishell *minishell, t_cmds *cmd_lst)
{
	char	*pwd;
	char	*oldpwd;

	(void)cmd_lst;
	pwd = get_env_value(minishell, "PWD");
	if (pwd == NULL)
		return (printf("Error: get_env_value failed\n"), 0);
	oldpwd = get_env_value(minishell, "OLDPWD");
	if (oldpwd == NULL)
		return (printf("Error: get_env_value failed\n"), 0);
	if (chdir(oldpwd) == -1)
	{
		perror("cd");
		return (0);
	}
	set_env_value(minishell, "PWD", oldpwd);
	set_env_value(minishell, "OLDPWD", pwd);
	free(pwd);
	free(oldpwd);
	return (1);
}*/
