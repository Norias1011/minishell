/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:02:35 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/04 16:59:46 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd_built(t_minishell *minishell, t_cmds *cmd_lst)
{
	char	*path;
	char	*pwd;
	int		i;

	i = 0;
	if (cmd_lst->args == NULL)
		return (cd_home(minishell), 0);
	else
	{
		while (cmd_lst->args[i] == ' ')
			i++;
		if (cmd_lst->args[i] != '\0')
			path = ft_strdup(cmd_lst->args + i);
		else
			return (cd_home(minishell), 0);
	}
	if (chdir(path) == -1)
		return (perror("cd"), 0);
	set_env_value(minishell, "OLDPWD", get_env_value(minishell, "PWD"));
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (perror("getcwd"), 0);
	set_env_value(minishell, "PWD", pwd);
	return (1);
}

void	cd_home(t_minishell *minishell)
{
	char	*home;
	char	*old;

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
		return ;
	}
	return ;
}
