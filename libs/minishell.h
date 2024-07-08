/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:04:32 by daortega          #+#    #+#             */
/*   Updated: 2024/07/08 15:12:23 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*-------SIGNALS---------*/
# define CTRL_C SIGINT
# define CTRL_BS SIGQUIT

/*--------LIBRARIES----------*/
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

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
}	t_redir;

typedef struct s_com
{
	char		**command;
	//struct		*s_redir;
	struct	s_com	*next;
}	t_com;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

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
int	count_lines(char **matrix);
int	ft_free_list(t_token *list);
int	ft_metachr(int c);
t_token	*ft_tokenlast(t_token *tkn);
void	print_list(t_token *list);
void	print_commands(t_com *com);
int	ft_addmetachr(char *line, int start, int x);
int	ft_addprint(char *line, int x);
int	ft_addend(char *line, int x);
int	ft_addquote(char *line, int start, int x);
char	**ft_lst_to_matrix(t_token *list);
t_com	*ft_lst_to_coms(t_token *list);
void	ft_free(char **str);
#endif
