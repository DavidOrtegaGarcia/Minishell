/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:04:32 by daortega          #+#    #+#             */
/*   Updated: 2024/07/15 16:55:50 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*-------SIGNALS---------*/
# define CTRL_C SIGINT
# define CTRL_BS SIGQUIT

/*------ERROR-MSG-----------*/
# define MSG_SE_PIPE "Syntax error near unexpected token '|'\n"
# define MSG_MLC_F "Error allocating memory\n"
# define MSG_OPEN_F "Error: %s couldn't be opened\n"
# define MSG_WNA "Wrong number of arguments\n"
# define MSG_CNR "Command not recognized\n"
# define MSG_FORK_F "Error creating a child procces\n"
# define MSG_FDE "The %s file doesn't exist\n"
# define MSG_PFE "Pipe function failed\n" 

/*-------ERROR-CODES-----*/
# define SE_PIPE 7
# define MLC_F 8
# define OPEN_F 9
# define WNA 10
# define CNR 11
# define FORK_F 12
# define FDE 13
# define PFE 14

/*--------LIBRARIES----------*/
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*---------STRUCTS----------*/
typedef struct s_token
{
	char			*content;
	struct s_token	*next;
}	t_token;

typedef enum s_redirect_type
{
	REDIRECT_NONE = 0,
	IN,
	HERE_DOC,
	OUT_TRUNC,
	OUT_APPEND,
}	t_type;

typedef struct s_redir
{
	t_type			type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_com
{
	char			**command;
	t_redir			*redir;
	struct	s_com	*next;
}	t_com;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

typedef struct s_exec
{
	int		*pids;
	int		fd[2];
	char	*env;
	int		*status;
}	t_exec;

/*--------------HEADERS--------------*/
t_env	*fill_l_env(char **env);
void	print_env(t_env *l_env);
char	*expansor(char *line, t_env *l_env, int exstat);
int		parse_input(int argc, char **argv, char **envp);
t_token	*ft_tokenize(char *line);
void	pre_execute(int argc, char **argv, char **envp);
int		compare_key(char *line, char *key);
void    signals(void);
void	print_list(t_token *list);
char	*find_path(char *command, t_env *l_env);
t_exec fill_exec(char *env, int *status, int n_com);
#endif
