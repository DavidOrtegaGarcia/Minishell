/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/07/22 16:52:04 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_env	*l_env;
	t_token	*list;
	t_com	*com;
	int	status;

	(void)argv;
	status = 0;
	if (argc != 1)
		return (perror(MSG_WNA), WNA);
	signals(DEFAULT);
	l_env = fill_l_env(env);
	if (l_env == NULL)
		return (perror(MSG_MLC_F), exit(MLC_F), MLC_F);
	print_env(l_env);
	line = readline("minishell$ ");
	while (line != NULL)
	{
      		if(line != NULL && line[0] != '\0') 
			  add_history(line);
		//TOKENIZER
		list = ft_tokenize(line);
                printf("In main: \nStatus %d\n", status);
                if (list == NULL)
                        exit(EXIT_FAILURE);
                //print_list(list);
		//PARSER
                com = ft_lst_to_coms(list, &status);
                ft_free_list(list);
                //print_commands(com);
                ft_countredir(com, &status);
                //print_commands(com);
                ft_free_coms(com);

		//EXPANSOR
		line = expansor(line, l_env, status);
		//EXEC
		//execute();

		free(line);
		line = readline("minishell$ ");
	}
	exit(EXIT_SUCCESS);
}
