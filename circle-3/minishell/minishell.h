/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamuzamm <mamuzamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:53:27 by mamuzamm          #+#    #+#             */
/*   Updated: 2026/01/29 04:20:14 by mamuzamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>

// general
# define TRUE 1
# define FALSE 0
# define LEFT 0
# define RIGHT 1
# define TNT 6201

// global variable
extern int			g_signal_caught;

// error_codes
typedef enum s_err_codes
{
	ERR_FORMAT = 1001,
	ERR_MALLOC,
	ERR_FORK,
	ERR_EXECVE,
	ERR_FILE,
	ERR_PIPE,
	ERR_CMD,
	ERR_READLINE,
	ERR_DUP
}					t_err_codes;

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}					t_env;

typedef struct s_export
{
	char			*exp;
	struct s_export	*next;
}					t_exp;

typedef struct s_pwd
{
	char			*pwd;
	char			*pwd_old;
	struct s_pwd	*next;
	t_env			*env_struct;
	t_exp			*exp_struct;
}					t_path;

typedef enum s_node_types
{
	NODE_CMD = 4201,
	NODE_OP,
	NODE_ARG,
	NODE_EXP,
	NODE_LOG_OP,
	NODE_REDIR,
	NODE_FILE,
	NODE_HDOC,
	NODE_LMTR
}					t_node_types;

typedef union s_data
{
	char			*exp;
	char			*log_op;
	char			op;
	char			*redir;
	char			*file;
	char			*cmd;
	char			**args;
	int				here_doc;
}					t_data;

typedef struct s_std_fds
{
	int				std_in;
	int				std_out;
	int				std_err;
}					t_std_fds;

typedef struct s_tree
{
	t_node_types	type;
	char			pos;
	int				level;
	t_data			data;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_shl
{
	t_tree			*head;
	t_path			*paths;
	t_std_fds		std_fds;
	int				inside_pipe;
	int				e_stat;
	char			**env;
}					t_shl;

void				rl_replace_line(const char *text, int clear_undo);

// helpers
int					ft_strlen(const char *str);
char				*ft_strchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, int start, int len);
int					ft_strncmp(const char *s1, const char *s2, int n);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_split(const char *s, char c);
char				*ft_itoa(int n);

// init_shell.c
t_shl				*init_shell(t_path *paths);
void				dup_fds(t_std_fds *std_fds);
void				reset_std_fds(t_std_fds *std_fds);

// tree_utils.c
void				add_node(t_tree **tree, t_tree *node, int side);
void				print_data(t_tree *tree);
void				print_tree(t_tree *tree);

// tokenization
int					strip_spaces(char **str);
t_tree				*tokenization(char *str, t_shl *shl);
t_tree				*tokenizer(char *str, t_tree **node);

// tokens_1.c
t_tree				*init_exp_node(char **str);
t_tree				*init_log_op_node(char spl_op);
t_tree				*init_op_node(char op, char *str);
t_tree				*init_redir_node(char *redir);
t_tree				*init_file_node(char *str);

// tokens_2.c
t_tree				*init_cmd_node(char **cmd);
t_tree				*init_args_node(char **args, char *cmd);
char				*exp_after_redir_node(char *str, char *first_half,
						int start);
char				*extract_file_name(char *str, int start);

// qoutes.c
int					inside_qoutes(char qoute, char *str, int i);
int					count_qoutes(char *str);
char				*remove_qoutes(char *str);
int					qoutes_checker(char *str);

// tokens_utils.c
// char				symbol_checker(char s);
int					redirection_ahead(char *str, int i);
int					spl_operator_ahead(char *str, int i);
int					operator_ahead(char *str, int i);
int					skip_spaces(char *str, int *i);

// error.c
int					print_error(int code);
void				print_exit(int code);
void				free_str(char **str);

// free_ast.c
t_tree				*free_ast(t_tree *tree);
void				free_ast_node(t_tree *node);
void				free_array(char **array);
void				cleanup_shell(t_shl *shl, int flag);
void				close_last_fd(t_tree *tree);

// splits.c
int					split_operator(char *str, t_tree **node, int i);
int					split_redirection(char *str, t_tree **node, int i);
int					split_cmd(char *str, int i, t_tree **node);
char				**split_args(char *str);

// splits_utils.c
char				*extract_cmd_from_redir(char *first_half, char *str,
						int start, int append);
int					count_args(char *str);
void				create_args_array(char *str, char ***args);
int					break_skip_spaces(char *str, int *i);
int					skip_qoutes(char *str, int *i);

// gallows.c
int					gallows(t_tree *tree, char **env, int pipe_flag,
						t_shl *shl);
void				execute(char **cmd, char *env[]);

// gallows_utils.c
char				*ft_cmd_exits(char **env, char *temp_cmd);
char				**array_dup(char **array);

// handle_nodes.c
void				handle_builtin(t_tree *tree, t_path *paths, t_shl *shl);
void				handle_cmd(t_tree *tree, char **env, int pipe_flag,
						t_shl *shl);
void				handle_redir(t_tree *tree, char **env, int pipe_flag,
						t_shl *shl);
void				handle_pipe(t_tree *tree, char **env, t_shl *shl);
int					handle_here_doc(int read_from);

// handle_utils.c
int					handle_input_redir(char *file_name, t_shl *shl);
int					handle_output_redir(char *file_name, t_shl *shl);
int					handle_append_redir(char *file_name, t_shl *shl);
pid_t				left_pipe(int *pipefd, t_tree *tree, t_shl *shl,
						char **env);
pid_t				right_pipe(int *pipefd, t_tree *tree, t_shl *shl,
						char **env);

// here_doc
int					find_docs(t_tree *tree, t_shl *shl);
int					ft_hdoc(char *limiter, t_shl *shl, pid_t *pid);

// syntax.c
int					check_log_op_node(t_tree *node);
int					check_op_node(t_tree *node);
int					check_redir_node(t_tree *node);
int					syntax_checker(t_tree *tree);

// expansions.c
char				*extract_env_var(char *str, int start, int *index);
char				*assign_env_value(char *env_var, t_env *env);
char				*expanded_str(char *str, char *env_var, int start, int end);
char				*env_expansion(char *str, t_env *env, t_shl *shl);
int					valid_expansion(char *str, int i);

// expansions_utils.c
void				expand_args(t_tree **arg_node, t_env *env, t_shl *shl);
void				expansions(t_tree **tree, t_env *env, t_shl *shl);
int					not_here_doc(char *str, int i);

// paths.c
t_path				*init_paths(char **env);
char				*get_cwd(void);
t_path				*int_cd(void);
int					list_length_env(t_env *env_list);

void				check_cwd(t_path **paths);

// signals.c
char				*signal_checkpoint(t_std_fds *std_fds, t_shl *shl);
void				handle_sigint(int sig);
void				handle_signals(int status, t_shl *shl);
void				signal_default(void);

// helpers - raph
int					ft_strlcpy(char *dst, const char *src, int dstsize);
void				*ft_calloc(int nmemb, int size);
void				ft_bzero(void *s, int n);
int					ft_atoi(char *s);
void				*ft_memset(void *b, int c, int len);
unsigned long long	ft_atol(char *s);

// for freeing;
// void				clear_all(t_path **paths, char **str);
void				ft_lstclear_path(t_path **lst);
void				ft_lstclear_env(t_env **lst);
void				ft_lstclear_exp(t_exp **lst);

// Builtins
void				echo_cmd(char **str, t_shl *shl);

void				pwd_cmd(char **str, t_shl *shl, t_path **paths);

void				exit_cmd(char **str, t_shl *shl);
void				valid_num(char *s, char **str, t_shl *shl);
void				error_msg(char **str, t_shl *shl);

void				env_cmd(char **str, t_path **paths, t_shl *shl);
t_env				*int_env(char **env);
void				appending_env(t_env **env, char *res);
t_env				*last_env(t_env *lst);

void				cd_cmd(char **str, t_path **paths, t_shl *shl);
char				*new_path(char *cwd, int id);
char				*get_home(t_path **paths);
int					valid_old_pwd(t_path **paths);
char				*switch_cd(t_path **paths);
t_path				*ft_lstlast_path(t_path *lst);
void				ft_lstadd_back_path(t_path **lst, t_path *new);
void				add_new_pwd(t_path **paths, t_path *new);
void				add_old_pwd(t_path **paths, t_path *new);
void				add_old_pwd_exp(t_path **paths, t_path *new);
void				ft_append(t_path **paths, char *res, t_shl *shl);
void				append_switch_struct(t_path **paths, t_path **temp);
int					check_old_pwd(t_path **paths);
void				check_exp_null(t_path **paths, t_exp *old_pwd);
void				check_env_null(t_path **paths, t_env *old_pwd);
char				*get_new_cwd(char *malloc_path);
void				error_msg_access(void);

void				unset_cmd(char **str, t_path **paths, t_shl *shl);
int					valid_unset(char *str);
int					check_prev_env(int i, t_path **paths, t_env *prev_env,
						t_env *tmp_env);
int					check_prev_exp(int i, t_path **paths, t_exp *prev_exp,
						t_exp *tmp_exp);
void				check_tmp_exp(t_exp *tmp, int *f);

void				export_cmd(char **str, t_path **paths, t_shl *shl);
void				sorted_exp(t_exp **head);
char				*checker_print(t_exp *tmp, int *i, int *check_with_equals);
t_env				*lstlast_env(t_env *lst);
char				**separator(char *str, int check_for_plus);
t_exp				*int_exp(char **env);
void				exp_print(t_path **paths, int i);
t_exp				*lstlast_exp(t_exp *lst);
void				ap_exp(t_exp **paths, char *res);
void				ap_env(t_env **env, char *res);
int					valid_export(char *str, char **res, char **sep,
						int check_for_plus);
void				export_t_env_plus(t_path **paths, char *tmp_char,
						char *sep);
void				export_t_exp_plus(t_path **paths, char *tmp_char,
						char *sep);
void				export_t_env(t_path **paths, char *tmp_char, char *sep,
						char *str);
void				export_t_exp(t_path **paths, char *tmp_char, char *sep,
						char *str);
int					plus_equals_check(char *str);
void				plus_equals_export(t_path **paths, char **sep, int *i);
void				normal_export(t_path **paths, char **sep, char *str,
						int *i);
char				*if_with_equals_env(t_env *tmp, char *holder,
						char *tmp_char, char *sep);
void				holder_is_equals_env(t_env *tmp, char *sep, char *tmp_char);
char				*if_with_equals_exp(t_exp *tmp, char *holder,
						char *tmp_char, char *sep);
void				holder_is_equals_exp(t_exp *tmp, char *sep, char *tmp_char);
void				checker_which_mode(char *str, char *tmp_char, int *check,
						int *tmp_char_len);
void				append_check_equals(t_path **paths, char *only_str,
						char *joined_str, int check);
void				exp_loop(t_exp *tmp, char *joined_str, int check);
void				check_sep_export(char **sep, int *i, int *exit_status);
void				plus_append(t_path **paths, char *tmp_char, char *sep);
void				tmp_looper(int *f, t_exp *tmp, int *tmp_char_len,
						char *tmp_char);

// main.c
void				reset_std_fds(t_std_fds *std_fds);

#endif