/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:04:32 by daortega          #+#    #+#             */
/*   Updated: 2024/05/28 12:12:30 by rpocater         ###   ########.fr       */
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
typedef struct s_token
{
	char			*content;
	struct s_token	*next;
}					t_token;
/*--------------HEADERS--------------*/
int		main(int argc, char *argv[], char *env[]);
int		parse_input(int argc, char **argv, char **envp);
char	**ft_tokenize(char *line);
void	pre_execute(int argc, char **argv, char **envp);
#endif
