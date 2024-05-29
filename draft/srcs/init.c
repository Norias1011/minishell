/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:11:46 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/29 14:08:44 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	int		i;
	int		add;
	t_token	*new;

	i = 0;
	add = 0;
	while (rl[i])
	{
		new = malloc(sizeof(t_token));
		if (!new)
			return ;
		if ((ft_isalpha(rl[i]) || ft_isdigit(rl[i]))
			|| (is_metachar(rl[i]) == 0))
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

int	init_mini_shell(t_minishell *minishell, char **env)
{
	ft_memset(minishell, 0, sizeof(t_minishell));
	if (!init_env(minishell, env))
	{
		printf("Error: init_env failed\n");
		return (0);
	}
	// init working directory
	// init le reste
	return (1);
}

int	init_env(t_minishell *minishell, char **env)
{
	int		i;
	t_env	*new_env;
	t_env	*tmp;

	i = 0;
	while (env[i])
	{
		new_env = (t_env *)malloc(sizeof(t_env));
		printf("Je malloc dans init_env\n");
		if (!new_env)
			return (0);
		new_env->key = ft_strndup(env[i], ft_strchr(env[i], '=') - env[i]);
		new_env->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		new_env->next = NULL;
		if (!minishell->env_s)
			minishell->env_s = new_env;
		else
		{
			tmp = minishell->env_s;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_env;
		}
		printf("key: %s\n", new_env->key);
		printf("value: %s\n", new_env->value);
		i++;
	}
	return (1);
}
