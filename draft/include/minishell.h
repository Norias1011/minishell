/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:25:39 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/22 13:27:36 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef enum token_lex
{
	NUMBER,
	STRING,
	SYMBOL,
	SPC,
	PIPE,
	ADD,
	SOUSTRACT,
	MULTI,
	DOLLAR,
	SLASH,
	BACKSLASH,
	COMA,
	DOT,
	DASH,
	QUOTE,
	DOUBLEQUOTE,
	UNDERSCORE,
	EQUAL,
	SEMICOLON,
	LEFT_ARROW,
	RIGHT_ARROW,
	QUOTE_STRING,
}		t_token_lex;

typedef struct s_token
{
	char			*content;
	t_token_lex	token;
	struct s_token	*next;
}		t_token;

int	ft_isalpha(int c);
unsigned int	ft_strlcpy(char *dest, char const *src, unsigned int size);
int	ft_isdigit(int c);
int	ft_strncmp(char const *str1, char const *str2, unsigned int n);
t_token	*check_command(t_token *token_lst);

#endif
