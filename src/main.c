/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:01:58 by daortega          #+#    #+#             */
/*   Updated: 2024/08/29 15:37:22 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_heredoc(char *file)
{
	if (unlink(file) != 0)
	{
		perror("Unlink function failed\n");
		exit(EXIT_FAILURE);
	}
}

void	clean_heredoc(t_com *com)
{
	t_redir	*aux;

	while (com != NULL)
	{
		aux = com->redir;
		while (aux != NULL)
		{
			if (aux->type == HERE_DOC)
				remove_heredoc(aux->file);
			aux = aux->next;
		}
		com = com->next;
	}
}

void	clean_and_free(t_com *com)
{
	clean_heredoc(com);
	ft_free_coms(com);
}

int	main(int argc, char *argv[], char *env[])
{
	int		status;
	char	*line;
	t_env	*l_env;
	t_com	*com;

	(void)argv;
	status = 0;
	if (argc != 1)
		return (ft_printf_fd(2, MSG_WNA), 1);
	signals(DEFAULT);
	l_env = fill_l_env(env);
	line = readline("minishell$ ");
	while (line != NULL)
	{
		if (line[0] != '\0')
			add_history(line);
		com = ft_token_and_parse(line, &status);
		expansor(com, l_env, status);
		heredoc(com);
		execute(com, &l_env, &status);
		signals(DEFAULT);
		clean_and_free(com);
		line = readline("minishell$ ");
	}
	return (exit(EXIT_SUCCESS), 0);
}
