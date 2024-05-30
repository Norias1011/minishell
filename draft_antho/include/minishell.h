/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:25:39 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/30 03:52:04 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define DEFAULT "\001\033[0;39m\002"
# define RED "\001\033[1;91m\002"
# define YELLOW "\001\033[1;93m\002"
# define MAGENTA "\001\033[1;95m\002"
# define GRAY "\001\033[1;90m\002"
# define BLUE "\e[1;34m"
# define GREEN "\e[1;32m"
# define CYAN "\e[1;36m"

typedef enum token_lex
{
	PIPE,      // |
	L_ARROW,   //<
	R_ARROW,   //>
	L_D_ARROW, //<<
	R_D_ARROW, //>>
	WORD,      // command
}					t_token_lex;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	t_token_lex		lex;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_minishell
{
	t_token			*token;
	t_env			*env_s;
	char			*prompt;
}					t_minishell;

/* main.c functions */

void				minishell_loop(t_minishell *minishell);

/* utils.c functions */

void				print_prompt(void);
void				clean_exit(t_minishell *minishell, int exno);
void				free_all(t_minishell *minishell);

/* init_all.c functions */

int					init_mini_shell(t_minishell *minishell, char **env);
int					init_env(t_minishell *minishell, char **env);

/* signal.c functions */

void				signal_handler(void);
void				nothing_signal(void);
void				new_prompt(int signo);

/* user_parsing.c functions */

bool				input_user_parser(t_minishell *minishell);

#endif
