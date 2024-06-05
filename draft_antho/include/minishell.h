/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:25:39 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/05 17:12:16 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
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
}						t_token_lex;

typedef	struct	s_file
{
	char	*name;
	char	*redir;
	struct	s_file	*next;
}			t_file;

typedef struct s_token
{
	char				*content;
	t_token_lex			token;
	struct s_token		*next;
}						t_token;

typedef struct s_cmds
{
	char			*command;
	char			*args;
	t_file			*file;
	struct s_cmds	*next;
}					t_cmds;


typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_garbage
{
	char				*value;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_minishell
{
	t_token				*token;
	t_env				*env_s;
	char				*prompt;
	char				**env;
	t_cmds				*cmds;
	t_garbage			*garbage;
}						t_minishell;

/* main.c functions */

void					minishell_loop(t_minishell *minishell);

/* utils.c functions */

void					print_prompt(void);
t_cmds					*get_last_cmd(t_cmds *stash);
int						get_arg_size(t_token **liste);
char					*get_token_name(t_token_lex token);

/* init_all.c functions */

int						init_mini_shell(t_minishell *minishell, char **env,
							t_garbage *garbage);
int						init_env(t_minishell *minishell, char **env);
char					*get_env_value(t_minishell *minishell, char *key);
char					*get_pwd(t_minishell *minishell);
void					set_env_value(t_minishell *minishell, char *key,
							char *value);
int						init_cd(t_minishell *minishell);
int						env_exist(t_minishell *minishell, char *key);
int						add_env(t_minishell *minishell, char *key, char *value);
void					remove_env(t_minishell *minishell, char *key);
int						init_garbage(t_garbage *garbage,
							t_minishell *minishell);
void					add_garbage(t_garbage *garbage, char *value);

/* signal.c functions */

void					signal_handler(void);
void					nothing_signal(void);
void					new_prompt(int signo);
void					signal_handler_bis(void);
void					new_prompt_bis(int signo);

/* user_parsing.c functions */

bool					input_user_parser(t_minishell *minishell);
char					*dollar_sign(t_minishell *minishell, char *args);

/* exec.c functions */

int						count_commands(t_cmds **cmd_lst);
void					handle_redirection(t_cmds *current_cmd, t_env *env_s,
							char **env, t_minishell *minishell);
void					pipe_pipe(t_cmds **cmd_lst, t_env *env_s, char **env,
							t_minishell *minishell);
void					execute_command(t_cmds *cmd_lst, t_env *env_s,
							char **env, t_minishell *minishell);

/* init_utils.c functions */

char					*dollar_quote(t_minishell *minishell, char *str);
int						dollar_quote_length(t_minishell *minishell, char *str);
int						check_dollar(t_minishell *minishell, char *rl,
							t_token *new, int i);
int						quote_handler(t_minishell *minishell, char *rl,
							t_token *new, int i);
int						check_arrow(char *rl, t_token *new, int i);
void					token(t_minishell *minishell, char *rl,
							t_token **token_lst);

/* spliter.c functions */

char					**split_paths(t_cmds *cmd, t_env *env,
							t_minishell *minishell);

/* token_utils.c functions */

t_token					*get_last_token(t_token *stash);
void					add_token(t_token **token_lst, t_token *new_token);
t_token_lex				get_symbol(char *symbol);
int						is_metachar(char c);
int						is_arrow(t_token *token);

/* token.c functions */

void					add_command(t_cmds **cmd_list, t_cmds *new);
int						token_string(char *rl, t_token *new, int i);
int						token_space(char *rl, t_token *new, int i);
int						token_symbol(char *rl, t_token *new, int i);

/* builtin.c functions */

void					echo(t_cmds *cmd_lst);
void					pwd(t_minishell *minishell, t_cmds *cmd_lst);
void					unset_built(t_minishell *minishell, t_cmds *cmd_lst);
void					check_unset(char *args, int *i, int *count);

/* env.c fnctions */

void					env_built(t_minishell *minishell, t_cmds *cmd_lst);

/* export.c functions */

void					export_built(t_minishell *minishell, t_cmds *cmd_lst);
void					check_export(char *args, int *i, int *count);
void					check_export_bis(char *args, int *i, int *count);
void					free_key_value(char *key, char *value);

/* exit.c functions */

int						exit_built(t_minishell *minishell, t_cmds *cmd_lst);
int						pipe_exist(t_cmds *cmd_lst);
int						check_exit(char *str);
int						count_word(char *str, char charset);
int						nextsteps(char c, char charset);

/* cd.c functions */

int						cd_built(t_minishell *minishell, t_cmds *cmd_lst);
void					cd_home(t_minishell *minishell);
void					erase_space(char *str);

/* utils2.c functions */

void	add_file(t_file **file_list, t_file *new_file);
void	add_command(t_cmds **cmd_list, t_cmds *new_cmd);
void					add_command(t_cmds **cmd_list, t_cmds *new_cmd);


/* command.c functions */

void					set_cmd_null(t_cmds *new);
void					cmd_args(t_cmds *new, t_token **tkn);
void					cmd_redir(t_cmds *new, t_token **tkn);
t_cmds					*create_cmd(t_token **tkn);
t_cmds					*token_to_commands(t_token *tkn);

/* free.c functions */

void					clean_exit(t_minishell *minishell, int exno);
void					free_all(t_minishell *minishell);
void					free_cmd(t_cmds *cmd);
void					free_cmds(t_cmds *cmds);
void					free_token(t_token *token);
void					free_env(t_env *env);
void					free_garbage(t_garbage *garbage);

#endif
