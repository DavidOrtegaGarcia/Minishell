/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/06/20 14:07:25 by rpocater         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_lines(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	ft_free_list(t_token *list)
{
	t_token	*elem;

	while (list != NULL)
	{
		elem = list;
		list = list->next;
		free(elem->content);
		free(elem);
	}
	return (0);
}

/*char	**ft_lst_to_matrix(t_token *list)
{
	int	i;
	char	**ret;
	t_token	*elem;

	ret = NULL;
	i = 0;
	if(list != NULL)
	{
		elem = list;
		while (elem->next != NULL)
		{
			elem = elem->next;
			i++;
		}
	}
	if (i > 0)
	{
		ret = (char **) malloc(sizeof(char *) * (i + 1));
		if (ret == NULL)
			return (NULL);
		elem = list;
		i = 0;
		while (elem->next != NULL)//possible problem
		{
			*(ret + i) = (char *) malloc(sizeof(char) * (ft_strlen(elem->content) + 1));
			*(ret + i) = ft_strdup(elem->content);
			elem = elem->next;
			i++;
		}
	}
	*(ret + i) = NULL;
	ft_free_list(list);
	return (ret);
}*/

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_env	*l_env;
	t_token	*command;

	(void)argv;
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
      	if(line != NULL && line[0] != '\0')
			add_history(line);
		//parseo
  		command = ft_tokenize(line);
		printf("In main: \n");
		if (command == NULL)
			exit(EXIT_FAILURE);
		print_list(command);
		//ft_free_list(command);
		//line = expansor(line, l_env, 1735);
		//if (line == NULL)
			//exit(EXIT_FAILURE);
		//ft_printf("%s\n", line);
		//execute();
		free(line);
		ft_free_list(command);
		line = readline("minishell$ ");
	}
	printf("HOLA\n");
	exit(EXIT_SUCCESS);
}
