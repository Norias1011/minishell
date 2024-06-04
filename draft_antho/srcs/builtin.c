/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:53:37 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/04 14:00:48 by akinzeli         ###   ########.fr       */
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
	while (cmd_lst->args[i] != '\0') // tant que y a des trucs a ecrire
	{
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

int	exit_built(t_minishell *minishell, t_cmds *cmd_lst)
{
	int	pipe;
	int	code_exit;

	code_exit = 0;
	pipe = pipe_exist(cmd_lst);
	if (pipe != 1)
		printf("exit\n");
	if (cmd_lst->args == NULL)
		code_exit = errno;
	else
		code_exit = check_exit(cmd_lst->args);
	if (code_exit == 255 || code_exit == 1)
		return (0);
	clean_exit(minishell, code_exit);
	return (1);
}

int	pipe_exist(t_cmds *cmd_lst)
{
	while (cmd_lst)
	{
		if (cmd_lst->redir != NULL && (strncmp(cmd_lst->redir, "|", 1) == 0))
			return (1);
		cmd_lst = cmd_lst->next;
	}
	return (0);
}

int	check_exit(char *str)
{
	int	i;
	int	code_exit;
	int	word;

	i = 0;
	code_exit = 0;
	word = count_word(str, ' ');
	if (word > 1)
	{
		// printf("exit\n");
		printf("exit: too many arguments\n");
		return (1);
	}
	while (str[i] != '\0')
	{
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		if (str[i] < '0' || str[i] > '9')
		{
			// printf("exit\n");
			printf("exit: %s: numeric argument required\n", str);
			return (255);
		}
		i++;
	}
	code_exit = ft_atoi(str);
	if (code_exit < 0)
	{
		// printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", str);
		return (255);
	}
	return (code_exit);
}

int	count_word(char *str, char charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (nextsteps(str[i], charset) == 0 && nextsteps(str[i + 1],
				charset) == 1)
		{
			count++;
		}
		i++;
	}
	return (count);
}

int	nextsteps(char c, char charset)
{
	if (c == charset)
	{
		return (1);
	}
	if (c == '\0')
	{
		return (1);
	}
	return (0);
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
