/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/07/22 13:59:57 by rpocater         ###   ########.fr       */
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
		return (printf("Wrong number of arguments\n"), -1);
	signals();
	l_env = fill_l_env(env);
	if (l_env == NULL)
		return (printf("Error allocating memory\n"), exit(EXIT_FAILURE), -1);
	//print_env(l_env);
	line = readline("minishell$ ");
	while (line != NULL)
	{
		if (line != NULL && line[0] != '\0')
			add_history(line);
		list = ft_tokenize(line);
		status = 0;
		printf("In main: \nStatus %d\n", status);
		if (list == NULL)
			exit(EXIT_FAILURE);
		//print_list(list);
		com = ft_lst_to_coms(list, &status);
		printf("After list to coms:\nStatus %d\n", status);
		ft_free_list(list);
		print_commands(com);
		ft_countredir(com, &status);
		printf("After add redir\n");
		print_commands(com);
		//printf("After second print commands\n");
		ft_free_coms(com);
		//printf("After free\n");
		//parseo
		//line = expansor(line, l_env, 1735);
		//if (line == NULL)
			//exit(EXIT_FAILURE);
		//ft_printf("%s\n", line);
		//printf("After execute\n");
		free(line);
		//ft_free(argv);
		line = readline("minishell$ ");
	}
	printf("HOLA\n");
	exit(EXIT_SUCCESS);
}
