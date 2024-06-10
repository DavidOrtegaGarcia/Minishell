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

int	main(int argc, char *argv[], char *env[])
{
	char *line;
	(void)argv;
	(void)env;
	t_token *command;
	if (argc != 1)
		return(printf("Wrong number of arguments\n"), -1);
	while (1)
	{
    	line = readline("minishell$ ");
		if(line != NULL && line[0] != '\0') 
			add_history(line);
		//parseo
		command = ft_tokenize(line);
		printf("In main: \n");
		print_list(command);
		//argc = count_lines(command);
		//pre_execute(argc, command, env);
		free(line);
		
	}
	printf("HOLA");
}
