/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:24:35 by daortega          #+#    #+#             */
/*   Updated: 2024/08/29 14:26:39 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	close_pipe(int in, int out)
{
	close(in);
	close(out);
}

char	*ft_strjoin_s(char const *s1, char const *s2)
{
	char	*sfinal;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	sfinal = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (sfinal == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		sfinal[i] = s1[i];
		i++;
	}
	sfinal[i] = '/';
	i++;
	while (i < ft_strlen(s1) + ft_strlen(s2) + 1)
		sfinal[i++] = s2[j++];
	sfinal[i] = '\0';
	return (sfinal);
}
