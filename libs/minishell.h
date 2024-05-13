/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:04:32 by daortega          #+#    #+#             */
/*   Updated: 2024/05/13 17:50:42 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

/*---------STRUCTS----------*/
typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
	struct s_env *prev;
}	t_env;

/*--------------HEADERS--------------*/
t_env *fill_t_env(char **env);
void	pre_execute(int argc, char **argv, char **envp);
#endif
