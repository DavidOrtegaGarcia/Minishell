/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:04:32 by daortega          #+#    #+#             */
/*   Updated: 2024/07/31 15:04:23 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*-------SIGNALS---------*/
# define CTRL_C SIGINT
# define CTRL_BS SIGQUIT
# define DEFAULT 0
# define CHILD 1

/*------ERROR-MSG-----------*/
# define MSG_SE_PIPE "Syntax error near unexpected token '|'\n"
# define MSG_MLC_F "Error allocating memory\n"
# define MSG_AT_END "Syntax error near the end\n"
# define MSG_DBL_RE "Syntax error caused by double redirections\n"
# define MSG_OPEN_F "Error: %s couldn't be opened\n"
# define MSG_WNA "Wrong number of arguments\n"
# define MSG_FORK_F "Error creating a child procces\n"
# define MSG_FDE "The %s file doesn't exist\n"
# define MSG_PFE "Pipe function failed\n" 
# define MSG_DF "Dup function failed\n"

/*-----MSG-COMMAND-ERRORS-------*/
# define MSG_CNA "%s: permission denied\n"
# define MSG_CNF "%s: command not found\n"
# define MSG_IAD "%s: is a directory\n"
# define MSG_NSF "%s: no such file or directory\n"
# define MSG_NAD "cd: %s: Not a directory\n"

/*-------ERROR-CODES-----*/
# define DBL_RE 6
# define SE_PIPE 7
# define MLC_F 8
# define AT_END 9
# define OPEN_F 15
# define WNA 10
# define CNR 11
# define FORK_F 12
# define FDE 13
# define PFE 14


/*------COMMAND-ERRORS------*/
# define CMD_NO_ACCESS 126
# define CMD_NOT_FOUND 127
# define IS_A_DIR 400
# define NO_SUCH_FILE 401

/*--------LIBRARIES----------*/
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <linux/limits.h>

/*---------STRUCTS----------*/
typedef enum s_redirect_type
{
	REDIRECT_NONE = 0,
	IN,
	HERE_DOC,
	OUT_TRUNC,
	OUT_APPEND,
}	t_type;

typedef struct s_token
{
	char		*content;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_type		type;
	char		*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_com
{
	char		**command;
	t_redir		*redir;
	struct s_com	*next;
}	t_com;

typedef struct s_env
{
	char		*key;
	char		*value;
	struct s_env	*next;
}	t_env;

typedef struct s_exec
{
	pid_t   *pids;
	int		fd[2];
	int		default_fd[2];
	char	**env;
	int		*status;
	int		n_com;
}	t_exec;

typedef	struct s_utils_exp
{
	int squotes;
	int exstat;
}	t_utils_exp;

/*--------------HEADERS--------------*/

//	EXPANSOR
t_env	*fill_l_env(char **env);
void	print_env(t_env *l_env);
void	expansor(t_com *com, t_env *l_env, int exstat);
int		compare_key(char *line, char *key);

//EXEC
void	signals(int process);
void	heredoc(t_com *command);
void	execute(t_com *t_command, t_env *l_env, char *env[], int *status);
int		get_n_commands(t_com *command);
char	*find_path(char *command, t_env *l_env);
t_exec  fill_exec(char **env, int *status, t_com *t_command);
void	make_redirections(t_redir *redir);
char	*ft_strjoin_s(char const *s1, char const *s2);
void	free_matrix(char **matrix);
void	close_pipe(int in, int out);

// BUILTINS
int 	check_builtin(char **com);
void	builtins(t_com *t_com, t_env *l_env, int *status);
void	echo(char **command, int *status);


/*General*/
int		parse_input(int argc, char **argv, char **envp);
int	count_lines(char **matrix);
void	ft_free(char **str);
t_com   *ft_token_and_parse(char *line, int *status);
char    *find_path_old(char **envp, char *str);

/*--------------TOKENIZE-------------*/
t_token *ft_tokenize(char *line);
void    print_list(t_token *list);
int     ft_free_list(t_token *list);
int     ft_metachr(int c);
t_token *ft_tokenlast(t_token *tkn);
int     ft_addmetachr(char *line, int start, int x);
int     ft_addprint(char *line, int x);
int     ft_addend(char *line, int x);
int     ft_addquote(char *line, int start, int x);

/*--------------PARSING--------------*/
void    make_redirections(t_redir *redir);
void    print_commands(t_com *com);
t_com   *ft_lst_to_coms(t_token *list, int *err);
void    ft_free_coms(t_com *com);
t_type  ft_type_redir(char *str);
t_redir *ft_red_last(t_redir *elem);
void    ft_countredir(t_com *list, int *err);
void    free_dpchar(char **com);
#endif
//Missing misaligned variable declarations
