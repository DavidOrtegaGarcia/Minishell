/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:04:32 by daortega          #+#    #+#             */
/*   Updated: 2024/05/24 16:07:31 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

/*---------STRUCTS----------*/
typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

/*--------------HEADERS--------------*/
t_env	*fill_l_env(char **env);
void	print_env(t_env *l_env);
char	*expansor(char *line, t_env *l_env);
void	pre_execute(int argc, char **argv, char **envp);
int		compare_key(char *line, char *key);
#endif
