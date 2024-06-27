/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:25:39 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/25 14:51:37 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/garbage.h"
# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
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
# define BLUE "\001\e[1;34m\002"
# define GREEN "\001\e[1;32m\002"
# define CYAN "\001\e[1;36m\002"

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

typedef struct s_file
{
	char			*name;
	char			*redir;
	struct s_file	*next;
}					t_file;

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
	t_file			*file;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_minishell
{
	t_token			*token;
	t_env			*env_s;
	char			*prompt;
	char			**env;
	t_cmds			*cmds;
	t_garbage		*garbage;
	t_file			*file;
	int				error;
	int				echo_flag;
}					t_minishell;

/* main.c functions */

void				minishell_loop(t_minishell *minishell);
char				**ft_split_modified(char const *s, char c, t_garbage **gc);
void				in_sep_f(int *in_sepp, int *count);
void				split_utils1(int *j, char **str, char charset, int *i);
void				split_utils2(int *k, int *j, char ***tab, t_garbage **gc);
void				split_utils3(int *j, char **str, char charset, int *i);
void				manage_integer(int *j, int *k, int *i);
void				manage_integer2(int *j, int *k, int *i);
void				init_integer(int *i, int *k, int *sep_len);
int					manage_integer3(int *j, int *sep_len);

/* exec_redir.c functions */

int					exec_arrow_r_d(t_file *file, int fd_file);
int					exec_arrow_r(t_file *file, int fd_file);
int					exec_arrow_l(t_file *file, int fd_file);
void				exec_heredoc(t_cmds **cmd);
void				exec_heredoc_bis(int *fd_file, char *line, t_cmds **cmd);

/* utils.c functions */

void				pipe_redir(t_cmds **cmd_lst, t_minishell *mini);
void				status_child(t_minishell *mini, int status);
void				print_prompt(void);
t_cmds				*get_last_cmd(t_cmds *stash);
int					get_arg_size(t_token **liste);

/* utils2.c functions */

void				add_command(t_cmds **cmd_list, t_cmds *new_cmd);
t_file				*get_last_file(t_file *stash);
void				add_file(t_file **file_list, t_file *new_file);
int					is_builtin(char *cmd);
int					count_commands(t_cmds **cmd_lst);

/* utils3.c functions */

void				exit_status_quote(t_minishell *mini, int *i, char **string);
void				pid_handler(int i, pid_t *p, int (*fd)[2], t_minishell *m);
int					echo_n_loop(t_cmds *cmd_lst, int i);
int					nextstep_md(char c, char charset);
void				set_cmd_null(t_cmds *new);

/* init_all.c functions */

int					init_mini_shell(t_minishell *minishell, char **env);
int					init_env(t_minishell *minishell, char **env, int i);
char				*get_env_value(t_minishell *minishell, char *key);
char				*get_pwd(t_minishell *minishell);
void				set_env_value(t_minishell *minishell, char *key,
						char *value);

/* init_all2.c functions */

int					init_cd(t_minishell *minishell);
int					env_exist(t_minishell *minishell, char *key);
int					add_env(t_minishell *minishell, char *key, char *value);
void				remove_env(t_minishell *minishell, char *key);

/* signal.c functions */

void				signal_handler(void);
void				nothing_signal(void);
void				new_prompt(int signo);
void				signal_handler_bis(void);
void				new_prompt_bis(int signo);

/* user_parsing.c functions */

bool				input_user_parser(t_minishell *minishell);
char				*dollar_sign(t_minishell *minishell, char *args);

/* exec.c functions */

void				heredoc(t_cmds *command, int fd);
void				execute_command(t_cmds *cmd_lst, t_env *env_s, char **env,
						t_minishell *minishell);
void				exec_builtin(t_minishell *minishell, t_cmds *cmd_lst);
void				free_args_and_path(char **args, char **paths,
						t_minishell *minishell);
void				free_execve(t_cmds *cmd, char **args, char **paths,
						t_minishell *mini);

/* init_utils.c functions */

int					dollar_quote_length(t_minishell *minishell, char *str);
int					check_dollar(t_minishell *minishell, char *rl, t_token *new,
						int i);
int					quote_handler(t_minishell *minishell, char *rl,
						t_token *new, int i);
int					check_arrow(char *rl, t_token *new, int i,
						t_minishell *minishell);
void				token(t_minishell *minishell, char *rl,
						t_token **token_lst);

/* spliter.c functions */

char				**split_paths(t_cmds **cmd, t_env *env,
						t_minishell *minishell);
char				**create_paths(char **paths, t_cmds *cmd,
						t_minishell *mini);
void				split_path_bis1(int *i, char ***paths, t_cmds **cmd,
						t_minishell *mini);

/* token_utils.c functions */

t_token				*get_last_token(t_token *stash);
void				add_token(t_token **token_lst, t_token *new_token);
t_token_lex			get_symbol(char *symbol);
int					is_metachar(char c);
int					is_arrow(t_token *token);

/* token.c functions */

int					quote_handler(t_minishell *mini, char *rl, t_token *new,
						int i);
int					check_arrow(char *rl, t_token *new, int i,
						t_minishell *mini);
int					check_dollar(t_minishell *m, char *rl, t_token *new, int i);
void				handle_token_speciaux(int *i, t_token *new, char *rl,
						t_minishell *mini);
void				token(t_minishell *mini, char *rl, t_token **token_lst);

/* builtin.c functions */

void				echo(t_cmds *cmd_lst, t_minishell *minishell);
void				pwd(t_minishell *minishell, t_cmds *cmd_lst);
void				unset_built(t_minishell *minishell, t_cmds *cmd_lst);
void				check_unset(char *args, int *i, int *count);
int					echo_n(t_cmds *cmd_lst, int i, int *new_line);

/* env.c fnctions */

void				env_built(t_minishell *minishell, t_cmds *cmd_lst);

/* export.c functions */

void				export_built(t_minishell *minishell, t_cmds *cmd_lst);
void				check_export(char *args, int *i, int *count,
						t_minishell *minishell);
void				check_export_bis(char *args, int *i, int *count);
void				free_key_value(char *key, char *value,
						t_minishell *minishell);
void				init_export_args_null(char **key, char **value, int *i,
						int *count);

/* exit.c functions */

int					exit_built(t_minishell *minishell, t_cmds *cmd_lst);
int					pipe_exist(t_cmds *cmd_lst);
int					check_exit(char *str, t_minishell *minishell);
int					check_error_num(int code_exit);

/* exit_utils.c functions */

int					count_word(char *str, char charset);
int					nextsteps(char c, char charset);

/* cd.c functions */

int					cd_built(t_minishell *minishell, t_cmds *cmd_lst);
void				cd_home(t_minishell *minishell);
void				erase_space(char *str);
char				*get_path_cd(t_minishell *minishell, t_cmds *cmd_lst);

/* dollar_quote.c functions */

char				*dollar_quote(t_minishell *mini, char *str);
void				malloc_str(char **str, int size, t_minishell *mini);
void				path_quote(char *str, int *i, char **string,
						t_minishell *mini);
void				exit_status_quote(t_minishell *mini, int *i, char **string);
int					check_dollar2(t_minishell *m, int j, char *tmp_string,
						t_token *new);
void				help_dollar_quote(int *i, char **w, t_minishell *m,
						char *str);

/* dollar_quote_length.c functions */

void				dollar_quote_length2(int *i, t_minishell *mini, int *x,
						char *str);
int					dollar_quote_length(t_minishell *mini, char *str);

/* utils2.c functions */

void				add_file(t_file **file_list, t_file *new_file);
void				add_command(t_cmds **cmd_list, t_cmds *new_cmd);
void				add_command(t_cmds **cmd_list, t_cmds *new_cmd);
int					is_builtin(char *cmd);
int					count_commands(t_cmds **cmd_lst);

/* pipe.c functions */

int					pipe_builtin(int nbr_cmd, t_cmds **cmd_lst,
						t_minishell *mini);
void				exec_pipes(int i, int nbr_cmd, int (*fd)[2]);
void				close_and_wait(int nbr_cmd, int (*fd)[2], t_minishell *mini,
						pid_t *pid);
void				pipe_redir(t_cmds **cmd_lst, t_minishell *mini);
void				pipe_pipe(t_cmds **cmd_lst, t_minishell *mini, int nbr_cmd);
void				status_child(t_minishell *mini, pid_t pid);

/* pipe_utils.c functions */

void				init_pipes(int (*fd)[2], int nbr_cmd);
void				pid_error(pid_t *pid, int (*fd)[2], t_minishell *mini);
void				malloc_pipe(int (**fd)[2], pid_t **pid, int nbr_cmd,
						t_minishell *mini);
void				close_unused_pipe(int i, int nbr_cmd, int (*fd)[2]);

/* command.c functions */

void				set_cmd_null(t_cmds *new);
void				cmd_args(t_cmds *new, t_token **tkn,
						t_minishell *minishell);
void				cmd_redir(t_cmds *new, t_token **tkn,
						t_minishell *minishell);
t_cmds				*create_cmd(t_token **tkn, t_minishell *minishell);
t_cmds				*token_to_commands(t_token *tkn, t_minishell *minishell);
void				create_cmd_bis(t_token **tkn, t_minishell *minishell,
						t_cmds *new);

/* free.c functions */

void				clean_exit(t_minishell *minishell, int exno);
void				free_all(t_minishell *minishell);

/* redirection.c functions */

int					exec_arrow_r_d(t_file *file, int fd_file);
int					exec_arrow_r(t_file *file, int fd_file);
int					exec_arrow_l(t_file *file, int fd_file);
void				exec_heredoc(t_cmds **current_cmd);
void				handle_redir(t_cmds *cmd, t_env *env_s, char **env,
						t_minishell *mini);
void				handle_redir_bis(t_cmds *cmd, int *check);
void				exec_heredoc_bis(int *fd_file, char *line, t_cmds **cmd);

/* token_split.c functions */

int					token_string(char *rl, t_token *new, int i,
						t_minishell *minishell);
int					token_space(char *rl, t_token *new, int i,
						t_minishell *minishell);
int					token_symbol(char *rl, t_token *new, int i,
						t_minishell *minishell);
int					simple_token(char *rl, int i, t_token *new,
						t_minishell *mini);

#endif
