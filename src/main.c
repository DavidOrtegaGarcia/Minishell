/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/07/17 15:32:23 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_env	*l_env;
	int		status;

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
		//parseo
  		/*command = ft_tokenize(line);
		printf("In main: \n");
		print_list(command);*/
		line = expansor(line, l_env, status);
		//execute();
		free(line);
		line = readline("minishell$ ");
	}
	exit(EXIT_SUCCESS);
}
