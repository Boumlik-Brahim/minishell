/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrahim <bbrahim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:32:10 by bbrahim           #+#    #+#             */
/*   Updated: 2022/07/01 17:42:32 by bbrahim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <stdint.h>
# include <stdbool.h>
# include <signal.h>
# include <limits.h>
# include <string.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define BUILTINS "echo cd pwd export unset env exit"
# define EXIT_ERROR ": numeric argument required"
# define CD_ERROR "cd: error retrieving current \
directory: getcwd: cannot access parent directories"
/* ---------------------------------- TypeDefs ------------------------------ */
typedef enum s_type
{
	CMD,
	CMD_NOT_FOUND,
	HERE_DOC,
	RED_IN,
	RED_APPEND,
	RED_OUT,
	INVALID_FILE,
	PIPE,
	WORD,
	SPACE_,
}	t_type;
typedef struct s_token
{
	struct s_token	*prev;
	int				token;
	char			*content;
	struct s_token	*next;
}	t_token;
typedef struct s_shell
{
	struct s_shell	*prev;
	int				token;
	char			*data;
	char			**switchs;
	int				file;
	struct s_shell	*next;
}	t_shell;
typedef struct s_env
{
	char			*key;
	char			*value;
	bool			print;
	struct s_env	*next;
}	t_env;
typedef struct s_data
{
	char	**env_tab;
	int		in_fd;
	int		pid;
	int		fd[2];
}	t_data;
typedef struct s_global
{
	int		exit_state;
	bool	forked;
}	t_global;

t_global	g_state;
/* ---------------------------------- TypeDefs ------------------------------ */
void	put_error(char *keyword, char *err);
/*--------------------------- get environment variables ----------------------*/

int		ft_env_size(t_env *env);
void	ft_envadd_back(t_env **lst, t_env *new);
t_env	*ft_envnew(char *key, char *value, bool print); //
char	*ft_get_keys(char *str, int c);
void	ft_create_env(t_env **list, char **env);
char	*ft_getenv(t_env *env, char *buffer);
void	ft_free_env(t_env *head, char error);

/*-------------------------------- Lexer -------------------------------------*/

char	is_last_operator(t_token *token);
char	check_last(t_token *token, int macro);
t_token	*tokennew(char *content, int token);
void	tokenadd_front(t_token **lst, t_token *new);
char	tokenadd_back(t_token **lst, t_token *new);
int		tokensize(t_token *lst);
t_token	*tokenlast(t_token *lst);
void	tokendelone(t_token *lst);
t_token	*lexer(char *line, t_env *env);

/*-------------------------------- Parser ------------------------------------*/

char	shelladd_front(t_shell **shell, t_shell *new);
char	shelladd_back(t_shell **shell, t_shell *new);
int		shell_size(t_shell *shell);
t_shell	*shell_new(int token, char *data, char **switchs, int file);
t_shell	*shell_last(t_shell *shell);
t_shell	*parser(char *line, t_env	*env);

/*-------------------------------- Lexer ------------------------------------*/

char	check_qoutes(char *line);
char	check_in_out_operators(char *line, char oper);
char	check_errors(char *token);
char	*expender(char *line, int *i, t_env *env);
char	*word_within_dqoutes(char *line, int *i, t_env *env, t_token *token);
char	*word_within_sqoutes(char *line, int *i);
char	*word(char *line, int *i);
char	get_word_util(char **s1, char **s2);
char	get_word(t_token **token, char *line, int *i, t_env *env);
char	get_here_doc(t_token **token, int *i);
char	get_red_in(t_token **token, int *i);
char	get_red_append(t_token **token, int *i);
char	get_red_out(t_token **token, int *i);
char	get_pipe(t_token **token, int *i);
char	get_space(t_token **token, char *line, int *i);
char	is_operators(char qoute, char a, char b);
char	get_operator(t_token **token, char *line, int *i);
char	tokenizer(t_token **token, char *line, t_env *env);

/*-------------------------------- Parser ------------------------------------*/

void	free_path(char **path);
char	**get_path(t_env *env);
char	*check_cmd(t_env *env, char *cmd);
char	**get_switchs(t_token *token);
t_shell	*get_cmd(t_env *env, t_token *token);
int		open_file(char *filename, int macro);
void	check_file_permession(char	*file, int macro);
char	is_operator(t_token *token);
void	process_operator(t_shell **shell, t_token **token);
void	store_data(t_shell **shell, int *files, t_shell *cmd,
			t_shell *here_doc);
void	process_data_util(t_shell **shell, t_token **token, t_env *env);
char	process_data(t_shell **shell, t_token *token, t_env *env);

/*-------------------------------- Executer ----------------------------------*/

void	ft_handle_error(char *cmd, char *arg, char *error);

void	ft_env_shlvl(t_env *env, char operator);
void	ft_empty_env(t_env **env);
int		ft_env(t_env *env);

void	ft_print_export(t_env *env, char **res);
void	ft_export_env(t_env *env, char *key, char *value, bool p);
int		ft_chk_export(char	*data);
void	ft_export_key_value(t_env *env, char	**data);
int		ft_export(t_env	*env, char	**data);

void	ft_delete_env(t_env	*current, t_env	*next);
void	ft_unset_env(t_env *env, char *data);
int		ft_chk_unset(char	*data);
int		ft_unset(t_env *env, char **data);

void	ft_cd_oldwd(t_env *env, char *oldwd);
void	ft_cd_wd(t_env *env, char *cwd);
int		ft_cd(t_env *env, char **data);

uint8_t	ft_exit_atoi(const char *str);
void	ft_chk_exit_args(char **data);
int		ft_chk_exit(char *data);
int		ft_exit(t_env *env, char **data);

int		ft_pwd(char	**data);

void	ft_print_echo(char	**data, int *i);
int		ft_chk_echo(char	*data);
int		ft_echo(char	**data);

void	ft_heredoc(char *delimiter);

void	ft_sigint_handler(int signal);
void	ft_sigquit_handler(int signal);
void	ft_eof(t_env *env);

int		ft_tolwr_strcmp(char *s1, char *s2);
int		ft_isbuiltin(char	**data);
int		ft_exec_builtin(t_env	*env, char	**data);
char	**ft_env_table(t_env *env);
int		ft_executecmd(t_shell *shell, char	**env_tab);

int		ft_ms_backbone(t_env	*env, t_shell	*shell, t_data *data);
/*-------------------------------- Executer ----------------------------------*/
#endif
