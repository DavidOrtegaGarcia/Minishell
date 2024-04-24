/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:37:14 by daortega          #+#    #+#             */
/*   Updated: 2023/10/06 14:26:29 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	static	fill_matrix(char *subs, char const *s, char c, int pstr)
{
	int	i;

	i = 0;
	while (s[pstr] == c)
		pstr++;
	while (s[pstr] != c && s[pstr] != '\0')
		subs[i++] = s[pstr++];
	subs[i] = '\0';
	return (pstr);
}

char static	**free_matrix(char **matrix, int i)
{
	while (--i > -1)
		free(matrix[i]);
	free(matrix);
	return (NULL);
}

int	static	chk_size(char const *s, char c, int pstr)
{
	int	result;

	result = 0;
	while (s[pstr] == c)
		pstr++;
	while (s[pstr] != c && s[pstr] != '\0')
	{
		result++;
		pstr++;
	}
	return (result);
}

int	static	chk_substrings(char const *s, char c)
{
	int	result;
	int	i;

	result = 0;
	i = 1;
	if (s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i - 1] != c)
			result++;
		i++;
	}
	if (s[i] == '\0' && s[i - 1] != c)
		result++;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		nsubs;
	int		i;
	int		pstr;

	i = 0;
	pstr = 0;
	nsubs = chk_substrings(s, c);
	matrix = (char **) malloc((nsubs + 1) * sizeof(char *));
	if (matrix == NULL)
		return (NULL);
	while (i < nsubs)
	{
		matrix[i] = (char *) malloc((chk_size(s, c, pstr) + 1) * sizeof(char));
		if (matrix[i] == NULL)
			return (free_matrix(matrix, i));
		pstr = fill_matrix(matrix[i], s, c, pstr);
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}
