/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/07/25 16:36:31 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_env	*l_env;
	t_token	*tokens;
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
    //print_env(l_env);
	line = readline("minishell$ ");
	while (line != NULL)
	{
		if (line[0] != '\0')
			add_history(line);
		//TOKENIZER
		tokens = ft_tokenize(line);
		//PARSER
		com = ft_lst_to_coms(tokens, &status);
		ft_free_list(tokens);
		ft_countredir(com, &status);
		//print_commands(com);
		//EXPANSOR
		expansor(com, l_env, status);
		//print_commands(com);
		//EXEC
		herdoc(com);
		execute(com, l_env, env, &status);
		//clean_heredoc(com);
		ft_free_coms(com);
		free(line);
		line = readline("minishell$ ");
	}
	exit(EXIT_SUCCESS);
	return(0);
}
