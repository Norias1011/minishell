/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:53:37 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/03 16:52:19 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo(t_cmds *cmd_lst)
{
	int	new_line;
	int	i;

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
	if (((cmd_lst->args[i] != '\0') && (strncmp(cmd_lst->args + i, "-n",
					3) == 0)) &&
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
	int		i;

	printf("cd called\n");
	i = 0;
	if (cmd_lst->args == NULL)
		return (cd_home(minishell));
	else
	{
		while (cmd_lst->args[i] == ' ')
			i++;
		if (cmd_lst->args[i] != '\0')
			path = ft_strdup(cmd_lst->args + i);
		else
			return (cd_home(minishell));
	}
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

void	cd_home(t_minishell *minishell)
{
	char	*home;
	char	*old;

	printf("BEFORE PWD: %s\n", get_env_value(minishell, "PWD"));
	printf("BEFORE OLDPWD: %s\n", get_env_value(minishell, "OLDPWD"));
	// set_env_value(minishell, "OLDPWD", get_env_value(minishell, "PWD"));
	old = get_env_value(minishell, "PWD");
	home = get_env_value(minishell, "HOME");
	if (home == NULL)
	{
		printf("Error: get_env_value failed\n");
		return ;
	}
	if (chdir(home) != -1)
	{
		set_env_value(minishell, "OLDPWD", old);
		set_env_value(minishell, "PWD", home);
		printf("AFTER PWD: %s\n", get_env_value(minishell, "PWD"));
		printf("AFTER OLDPWD: %s\n", get_env_value(minishell, "OLDPWD"));
		return ;
	}
	return ;
}

void	export_built(t_minishell *minishell, t_cmds *cmd_lst)
{
	char	*key;
	char	*value;
	int		i;
	int		count;

	i = 0;
	count = 0;
	key = NULL;
	value = NULL;
	if (cmd_lst->args == NULL)
		return (env_built(minishell, cmd_lst));
	while (cmd_lst->args[i] != '\0' && cmd_lst->args[i] != '=')
	{
		while (cmd_lst->args[i] == ' ' && cmd_lst->args[i] != '\0')
			i++;
		while (cmd_lst->args[i] != ' ' && cmd_lst->args[i] != '\0'
			&& cmd_lst->args[i] != '=')
		{
			i++;
			count++;
		}
	}
	if (cmd_lst->args[i] == '=')
		key = ft_substr(cmd_lst->args, i - count, count);
	else
		return ;
	i++;
	count = 0;
	while (cmd_lst->args[i] != '\0')
	{
		while (cmd_lst->args[i] == ' ' && cmd_lst->args[i] != '\0')
			i++;
		while (cmd_lst->args[i] != ' ' && cmd_lst->args[i] != '\0')
		{
			i++;
			count++;
		}
	}
	if (cmd_lst->args[i] == '\0' && key != NULL)
		value = ft_substr(cmd_lst->args, i - count, count);
	if (env_exist(minishell, key) == 0)
		add_env(minishell, key, value);
	else
		set_env_value(minishell, key, value);
	free(key);
	free(value);
}

void	unset_built(t_minishell *minishell, t_cmds *cmd_lst)
{
	char	*key;
	int		i;
	int		count;

	key = NULL;
	i = 0;
	count = 0;
	if (cmd_lst->args == NULL)
		return ;
	while (cmd_lst->args[i] != '\0')
	{
		while (cmd_lst->args[i] == ' ' && cmd_lst->args[i] != '\0')
			i++;
		while (cmd_lst->args[i] != ' ' && cmd_lst->args[i] != '\0')
		{
			i++;
			count++;
		}
	}
	key = ft_substr(cmd_lst->args, i - count, count);
	if (env_exist(minishell, key) == 1)
	{
		remove_env(minishell, key);
		free(key);
	}
	else
	{
		free(key);
		return ;
	}
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
