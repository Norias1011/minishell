/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:02:35 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/25 15:06:14 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	erase_space(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != ' ')
		i++;
	while (str[i + j] == ' ')
		j++;
	if (i + j == ft_strlen(str))
		str[i] = '\0';
}

char	*get_path_cd(t_minishell *mini, t_cmds *cmd_lst)
{
	int	i;

	i = 0;
	while (cmd_lst->args[i] == ' ')
		i++;
	return (ft_strdup(cmd_lst->args + i, &(mini->garbage)));
}

int	cd_built(t_minishell *mini, t_cmds *cmd_lst)
{
	char	*path;
	char	*pwd;

	path = NULL;
	if (cmd_lst->args == NULL || get_env_value(mini, "PWD") == NULL)
		return (cd_home(mini), 0);
	else
	{
		if (count_word(cmd_lst->args, ' ') > 1)
			return (write(2, " too many arguments", 19), mini->error = 1, 0);
		path = get_path_cd(mini, cmd_lst);
		if (path[0] == '\0')
			return (cd_home(mini), 0);
		erase_space(path);
	}
	if (chdir(path) == -1)
		return (perror("cd"), mini->error = 1, 0);
	set_env_value(mini, "OLDPWD", get_env_value(mini, "PWD"));
	pwd = getcwd(NULL, 0);
	g_add(&(mini->garbage), pwd);
	if (pwd == NULL)
		return (perror("getcwd"), 0);
	set_env_value(mini, "PWD", pwd);
	return (1);
}

void	cd_home(t_minishell *mini)
{
	char	*home;
	char	*old;

	old = get_env_value(mini, "PWD");
	home = get_env_value(mini, "HOME");
	if (home == NULL || old == NULL)
	{
		printf("Error: get_env_value failed\n");
		return ;
	}
	if (chdir(home) != -1)
	{
		set_env_value(mini, "OLDPWD", old);
		set_env_value(mini, "PWD", home);
		return ;
	}
	return ;
}
