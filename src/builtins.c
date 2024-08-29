/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:54:27 by daortega          #+#    #+#             */
/*   Updated: 2024/08/29 14:30:18 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_env *l_env, int *status)
{
	print_env(l_env);
	*status = 0;
}

void	pwd(int *status)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		perror("getcwd() error\n");
		*status = EXIT_FAILURE;
	}
	*status = EXIT_SUCCESS;
}

char	*find_home(t_env *l_env)
{
	while (l_env != NULL)
	{
		if (ft_strcmp(l_env->key, "HOME") == 0)
			return (l_env->value);
		l_env = l_env->next;
	}
	return (NULL);
}

int	cd(char **command, t_env *l_env)
{
	struct stat	path_stat;
	char		*home;

	if (command[1] == NULL)
	{
		home = find_home(l_env);
		if (home == NULL)
			return (ft_printf("cd: HOME not set\n"), EXIT_FAILURE);
		chdir(home);
	}
	else
	{
		if (access(command[1], F_OK) == 0)
		{
			if (stat(command[1], &path_stat) != 0)
				return (perror("Stat failed\n"), EXIT_FAILURE);
			if (!S_ISDIR(path_stat.st_mode))
				return (ft_printf(MSG_NAD, command[1]), EXIT_FAILURE);
			chdir(command[1]);
		}
		else
			return (ft_printf(MSG_NSF, command[1]), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	builtins(t_com *t_command, t_env **l_env, int *status)
{
	if (ft_strcmp(t_command->command[0], "echo") == 0)
		echo(t_command->command, status);
	else if (ft_strcmp(t_command->command[0], "cd") == 0)
		*status = cd(t_command->command, *l_env);
	else if (ft_strcmp(t_command->command[0], "pwd") == 0)
		pwd(status);
	else if (ft_strcmp(t_command->command[0], "export") == 0)
		export(t_command, l_env, status);
	else if (ft_strcmp(t_command->command[0], "unset") == 0)
		unset(t_command, l_env, status);
	else if (ft_strcmp(t_command->command[0], "env") == 0)
		env(*l_env, status);
	else if (ft_strcmp(t_command->command[0], "exit") == 0)
		*status = ft_exit(t_command->command);
}
