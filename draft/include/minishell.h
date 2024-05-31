/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:25:39 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/30 15:42:55 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/history.h>
# include <readline/readline.h>
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
#include <fcntl.h>
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
	STRING,
	SYMBOL,
	SPC,
	PIPE,
	DOLLAR,
	DASH,
	QUOTE,
	DOUBLEQUOTE,
	UNDERSCORE,
	L_ARROW,
	R_ARROW,
	L_D_ARROW,
	R_D_ARROW,
	QUOTE_STRING,
}					t_token_lex;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*content;
	t_token_lex		token;
	struct s_token	*next;
}					t_token;

typedef struct s_cmds
{
	char			*command;
	char			*args;
	char			*file;
	char			*redir;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_minishell
{
	t_token			*token;
	t_env			*env_s;
	t_cmds			*cmds;
	char			*prompt;
	char			**env;
}					t_minishell;

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

bool				input_user_parser(t_minishell *minishell);

char				**split_paths(t_cmds *cmd, t_env *env);
int					get_arg_size(t_token **liste);
t_cmds				*get_last_cmd(t_cmds *stash);
int					token_string(char *rl, t_token *new, int i);
int					token_space(char *rl, t_token *new, int i);
int					token_symbol(char *rl, t_token *new, int i);
void				add_token(t_token **token_lst, t_token *new_token);
t_token_lex			get_symbol(char *symbol);
int					is_metachar(char c);
void				free_token_lst(t_token *token_lst);
t_cmds				*token_to_commands(t_token *token_list);
void				token(char *rl, t_token **token_lst);
void				execute_command(t_cmds *cmd_lst, t_env *env_s, char **env);
int					ft_isalpha(int c);
unsigned int		ft_strlcpy(char *dest, char const *src, unsigned int size);
int					ft_isdigit(int c);
int					ft_strncmp(char const *str1, char const *str2,
						unsigned int n);
t_token				*check_command(t_token *token_lst);

#endif
